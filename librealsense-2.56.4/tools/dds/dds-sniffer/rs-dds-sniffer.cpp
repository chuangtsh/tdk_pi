// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022-4 Intel Corporation. All Rights Reserved.

#include "rs-dds-sniffer.h"

#include <thread>
#include <memory>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/log/Log.hpp>
#include <fastrtps/types/DynamicDataHelper.hpp>
#include <fastrtps/types/DynamicDataFactory.h>
#include <fastdds/rtps/builtin/data/WriterProxyData.h>
#include <fastdds/rtps/builtin/data/ReaderProxyData.h>

#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <tclap/SwitchArg.h>

#include <realdds/dds-utilities.h>
#include <realdds/dds-guid.h>
#include <realdds/dds-log-consumer.h>
#include <realdds/dds-serialization.h>

#include <rsutils/os/special-folder.h>
#include <rsutils/os/executable-name.h>
#include <rsutils/easylogging/easyloggingpp.h>
#include <rsutils/json.h>
#include <rsutils/json-config.h>
#include <rsutils/ios/field.h>
#include <rsutils/string/from.h>

using namespace TCLAP;
using namespace eprosima::fastdds::dds;
using namespace eprosima::fastrtps::types;

static eprosima::fastrtps::rtps::GuidPrefix_t std_prefix;

static inline realdds::print_guid print_guid( realdds::dds_guid const & guid )
{
    return realdds::print_guid( guid, std_prefix );
}


int main( int argc, char ** argv ) try
{
    realdds::dds_domain_id domain = -1;  // from settings; default to 0
    uint32_t seconds = 0;

    CmdLine cmd( "librealsense rs-dds-sniffer tool", ' ' );
    SwitchArg snapshot_arg( "s", "snapshot", "run momentarily taking a snapshot of the domain" );
    SwitchArg machine_readable_arg( "m", "machine-readable", "output entities in a way more suitable for automatic parsing" );
    SwitchArg topic_samples_arg( "t", "topic-samples", "register to topics that send TypeObject and print their samples" );
    SwitchArg debug_arg( "", "debug", "Enable debug logging", false );
    SwitchArg participants_arg( "", "participants", "Show participants and quit; implies --snapshot", false );
    SwitchArg topics_arg( "", "topics", "Show topics and quit; implies --snapshot", false );
    ValueArg< realdds::dds_domain_id > domain_arg( "d", "domain", "select domain ID to listen on", false, 0, "0-232" );
    ValueArg< std::string > root_arg( "r", "root", "filter anything not inside this root path", false, "", "" );
    cmd.add( snapshot_arg );
    cmd.add( machine_readable_arg );
    cmd.add( topic_samples_arg );
    cmd.add( domain_arg );
    cmd.add( debug_arg );
    cmd.add( participants_arg );
    cmd.add( topics_arg );
    cmd.add( root_arg );
    cmd.parse( argc, argv );

    bool participants = participants_arg.isSet();
    bool topics = topics_arg.isSet();
    bool machine_readable = machine_readable_arg.isSet();
    bool topic_samples = topic_samples_arg.isSet();
    bool snapshot = snapshot_arg.isSet() || participants || topics;

    // Intercept DDS messages and redirect them to our own logging mechanism
    rsutils::configure_elpp_logger( debug_arg.isSet() );
    eprosima::fastdds::dds::Log::ClearConsumers();
    eprosima::fastdds::dds::Log::RegisterConsumer( realdds::log_consumer::create() );

    if( snapshot )
    {
        seconds = ( participants && ! topics ) ? 1 : 3;  // don't need as much time to detect participants
    }

    if( domain_arg.isSet() )
    {
        domain = domain_arg.getValue();
        if( domain > 232 )
        {
            LOG_ERROR( "Invalid domain value, enter a value in the range [0, 232]" );
            return EXIT_FAILURE;
        }
    }

    dds_sniffer sniffer;

    sniffer.print_discoveries( ! snapshot );
    sniffer.print_machine_readable( machine_readable );
    sniffer.print_topic_samples( topic_samples && ! snapshot );

    sniffer.set_root( root_arg.getValue() );

    if( ! sniffer.init( domain ) )
    {
        LOG_ERROR( "Initialization failure" );
        return EXIT_FAILURE;
    }


    std_prefix = sniffer.get_participant().guid().guidPrefix;

    if( ! machine_readable && ! snapshot )
    {
        std::cout << rsutils::os::executable_name() << " listening on domain " << sniffer.get_participant().domain_id();
        std::cout << " (press Ctrl+C to stop)";
        std::cout << std::endl;
    }

    if( ! snapshot )
    {
        // Wait until user presses Ctrl+C
        std::cin.ignore( std::numeric_limits< std::streamsize >::max() );
    }
    else
    {
        // We need to allow enough time to pick up all participants, writers, etc. -- it takes time
        std::this_thread::sleep_for( std::chrono::seconds( seconds ) );
    }

    if( participants )
    {
        sniffer.print_participants( topics, true );
    }
    else if( topics )
    {
        sniffer.print_topics_for( realdds::dds_guid_prefix() );
    }
    else if( snapshot )
    {
        if( machine_readable )
            sniffer.print_topics_machine_readable();
        else
            sniffer.print_topics();
    }



    return EXIT_SUCCESS;
}
catch( const TCLAP::ExitException & )
{
    LOG_ERROR( "Undefined exception while parsing command line arguments" );
    return EXIT_FAILURE;
}
catch( const TCLAP::ArgException & e )
{
    LOG_ERROR( e.what() );
    return EXIT_FAILURE;
}
catch( const std::exception & e )
{
    LOG_ERROR( e.what() );
    return EXIT_FAILURE;
}

dds_sniffer::dds_sniffer()
    : _participant()
    , _reader_listener( _discovered_types_datas )
{
}

dds_sniffer::~dds_sniffer()
{
    for( const auto & it : _discovered_types_readers )
    {
        DDS_API_CALL_NO_THROW( _discovered_types_subscriber->delete_datareader( it.first ) );  // If not empty than _discovered_types_subscriber != nullptr
        DDS_API_CALL_NO_THROW( _participant.get()->delete_topic( it.second ) );
    }

    if( _discovered_types_subscriber != nullptr )
    {
        DDS_API_CALL_NO_THROW( _participant.get()->delete_subscriber( _discovered_types_subscriber ) );
    }

    _discovered_types_readers.clear();
    _discovered_types_datas.clear();
}


static rsutils::json load_settings( rsutils::json const & local_settings )
{
    // Load the realsense configuration file settings
    std::string const filename = rsutils::os::get_special_folder( rsutils::os::special_folder::app_data ) + "realsense-config.json";
    auto config = rsutils::json_config::load_from_file( filename );

    // Take just the 'context' part
    config = rsutils::json_config::load_settings( config, "context", "config-file" );

    // Take the "dds" settings only
    config = config.nested( "dds" );

    // We should always have DDS enabled
    if( config.is_object() )
        config.erase( "enabled" );

    // Patch the given local settings into the configuration
    config.override( local_settings, "local settings" );

    return config;
}


bool dds_sniffer::init( realdds::dds_domain_id domain )
{
    // Set callbacks before calling _participant.init(), or some events, specifically on_participant_added, might get lost
    _participant.create_listener( &_listener )
        ->on_writer_added( [this]( eprosima::fastrtps::rtps::WriterProxyData const & data ) {
            on_writer_added( data );
        } )
        ->on_writer_removed( [this]( realdds::dds_guid guid, char const * topic_name ) {
            on_writer_removed( guid, topic_name );
        } )
        ->on_reader_added( [this]( eprosima::fastrtps::rtps::ReaderProxyData const & data ) {
            on_reader_added( data );
        } )
        ->on_reader_removed( [this]( realdds::dds_guid guid, char const * topic_name ) {
            on_reader_removed( guid, topic_name );
        } )
        ->on_participant_added( [this]( realdds::dds_guid guid, char const * participant_name ) {
            on_participant_added( guid, participant_name );
        } )
        ->on_participant_removed( [this]( realdds::dds_guid guid, char const * participant_name ) {
            on_participant_removed( guid, participant_name );
        } )
        ->on_type_discovery( [this]( char const * topic_name, DynamicType_ptr dyn_type ) {
            on_type_discovery( topic_name, dyn_type );
        } );

    rsutils::json settings( rsutils::json::object() );
    settings = load_settings( settings );
    _participant.init( domain, rsutils::os::executable_name(), std::move( settings ) );

    return _participant.is_valid();
}


static bool filter_topic( std::string const & topic, std::string const & root )
{
    if( root.empty() )
        return false;
    if( 0 == strncmp( topic.data(), root.data(), root.length() ) )
        return false;
    if( 0 == strncmp( topic.data(), "rt/", 3 )
        && 0 == strncmp( topic.data() + 3, root.data(), root.length() ) )
        return false;
    return true;
}


void dds_sniffer::on_writer_added( eprosima::fastrtps::rtps::WriterProxyData const & data )
{
    if( _print_discoveries )
    {
        print_writer_discovered( data.guid(), data.topicName().c_str(), true );
    }

    save_topic_writer( data );
}

void dds_sniffer::on_writer_removed( realdds::dds_guid guid, const char * topic_name )
{
    if( _print_discoveries )
    {
        print_writer_discovered( guid, topic_name, false );
    }

    remove_topic_writer( guid, topic_name );
}

void dds_sniffer::on_reader_added( eprosima::fastrtps::rtps::ReaderProxyData const & data )
{
    if( _print_discoveries )
    {
        print_reader_discovered( data.guid(), data.topicName().c_str(), true );
    }
    save_topic_reader( data );
}

void dds_sniffer::on_reader_removed( realdds::dds_guid guid, const char * topic_name )
{
    if( _print_discoveries )
    {
        print_reader_discovered( guid, topic_name, false );
    }

    remove_topic_reader( guid, topic_name );
}

void dds_sniffer::on_participant_added( realdds::dds_guid guid, const char * participant_name )
{
    if( _print_discoveries )
    {
        print_participant_discovered( guid, participant_name, true );
    }

    std::lock_guard< std::mutex > lock( _dds_entities_lock );

    _discovered_participants[guid] = participant_name;
}

void dds_sniffer::on_participant_removed( realdds::dds_guid guid, const char * participant_name )
{
    if( _print_discoveries )
    {
        print_participant_discovered( guid, participant_name, false );
    }

    std::lock_guard< std::mutex > lock( _dds_entities_lock );

    _discovered_participants.erase( guid );
}

void dds_sniffer::on_type_discovery( char const * topic_name, DynamicType_ptr dyn_type )
{
    // Register type with participant
    TypeSupport type_support( DDS_API_CALL( new DynamicPubSubType( dyn_type ) ) );
    DDS_API_CALL( type_support.register_type( _participant.get() ) );
    if( _print_discoveries )
        std::cout << "+Topic '" << topic_name << "' of type '" << type_support->getName() << "'" << std::endl;

    if( _print_topic_samples )
    {
        // Create subscriber, topic and reader to receive instances of this topic
        if( _discovered_types_subscriber == nullptr )
        {
            _discovered_types_subscriber = DDS_API_CALL( _participant.get()->create_subscriber( SUBSCRIBER_QOS_DEFAULT,
                                                                                                nullptr ) );
            if( _discovered_types_subscriber == nullptr )
            {
                LOG_ERROR( "Cannot create subscriber for discovered type '" << topic_name );
                return;
            }
        }

        Topic * topic = DDS_API_CALL( _participant.get()->create_topic( topic_name, type_support->getName(),
                                                                        TOPIC_QOS_DEFAULT ) );
        if( topic == nullptr )
        {
            LOG_ERROR( "Cannot create topic for discovered type '" << topic_name );
            return;
        }

        StatusMask sub_mask = StatusMask::subscription_matched() << StatusMask::data_available();
        DataReaderQos rqos = DATAREADER_QOS_DEFAULT;
        rqos.endpoint().history_memory_policy = eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
        DataReader * reader = DDS_API_CALL( _discovered_types_subscriber->create_datareader( topic,
                                                                                                rqos,
                                                                                                &_reader_listener,
                                                                                                sub_mask ) );
        if( reader == nullptr )
        {
            LOG_ERROR( "Cannot create reader for discovered type '" << topic_name );
            DDS_API_CALL( _participant.get()->delete_topic( topic ) );
            return;
        }
        _discovered_types_readers[reader] = topic;

        DynamicData_ptr data( DDS_API_CALL( DynamicDataFactory::get_instance()->create_data( dyn_type ) ) );
        _discovered_types_datas[reader] = data;
    }
}

dds_sniffer::dds_reader_listener::dds_reader_listener( std::map< DataReader *, DynamicData_ptr > & datas )
    : _datas( datas )
{
}

void dds_sniffer::dds_reader_listener::on_data_available( DataReader * reader )
{
    const TopicDescription * topic_desc = DDS_API_CALL( reader->get_topicdescription() );
    std::cout << "Received topic " << topic_desc->get_name() << " of type " 
              << topic_desc->get_type_name() << std::endl;

    auto dit = _datas.find( reader );

    if( dit != _datas.end() )
    {
        DynamicData_ptr data = dit->second;
        realdds::dds_sample sample;
        if( DDS_API_CALL( reader->take_next_sample( data.get(), &sample ) ) == ReturnCode_t::RETCODE_OK )
        {
            if( sample.valid_data )
            {
                DynamicDataHelper::print( data );
            }
        }
    }
}

void dds_sniffer::dds_reader_listener::on_subscription_matched( DataReader * reader, const SubscriptionMatchedStatus & info )
{
    if( info.current_count_change == 1 )
    {
        LOG_DEBUG( "Subscriber matched by reader " << print_guid( reader->guid() ) );
    }
    else if( info.current_count_change == -1 )
    {
        LOG_DEBUG( "Subscriber unmatched by reader " << print_guid( reader->guid() ) );
    }
    else
    {
        LOG_ERROR( info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change" );
    }
}

void dds_sniffer::save_topic_writer( eprosima::fastrtps::rtps::WriterProxyData const & data )
{
    std::lock_guard< std::mutex > lock( _dds_entities_lock );

    auto & info = _topics_info_by_name[data.topicName().c_str()];
    if( data.typeName().size() )
        info.type_info = rsutils::string::from( realdds::print_writer_info( data ) );
    info.writers.insert( data.guid() );
}

void dds_sniffer::remove_topic_writer( realdds::dds_guid guid, const char * topic_name )
{
    std::lock_guard< std::mutex > lock( _dds_entities_lock );

    auto topic_entry = _topics_info_by_name.find( topic_name );
    if( topic_entry != _topics_info_by_name.end() )
    {
        topic_entry->second.writers.erase( guid );
        if( topic_entry->second.writers.empty() && topic_entry->second.readers.empty() )
        {
            _topics_info_by_name.erase( topic_entry );
        }
    }
}

void dds_sniffer::save_topic_reader( eprosima::fastrtps::rtps::ReaderProxyData const & data )
{
    std::lock_guard< std::mutex > lock( _dds_entities_lock );

    auto & info = _topics_info_by_name[data.topicName().c_str()];
    if( data.typeName().size() )
        info.type_info = rsutils::string::from( realdds::print_reader_info( data ) );
    info.readers.insert( data.guid() );
}

void dds_sniffer::remove_topic_reader( realdds::dds_guid guid, const char * topic_name )
{
    std::lock_guard< std::mutex > lock( _dds_entities_lock );

    auto topic_entry = _topics_info_by_name.find( topic_name );
    if( topic_entry != _topics_info_by_name.end() )
    {
        topic_entry->second.readers.erase( guid );
        if( topic_entry->second.writers.empty() && topic_entry->second.readers.empty() )
        {
            _topics_info_by_name.erase( topic_entry );
        }
    }
}

dds_sniffer::topic_display_stats dds_sniffer::calc_topic_display_stats() const
{
    topic_display_stats stats{ 0 };

    for( auto & topic : _topics_info_by_name )  //_dds_entities_lock locked by print_topics()
    {
        if( filter_topic( topic.first, _root ) )
            continue;
        // Use / as delimiter for nested topic names
        size_t indentation = std::count( topic.first.begin(), topic.first.end(), '/' );
        if( indentation >= stats.max_indent )
        {
            stats.max_indent = indentation + 1;  //+1 for Reader/Writer indentation
        }
        if( topic.first.length() > stats.max_len )
            stats.max_len = topic.first.length();
    }

    return stats;
}

void dds_sniffer::print_writer_discovered( realdds::dds_guid guid,
                                           const char * topic_name,
                                           bool discovered ) const
{
    if( filter_topic( topic_name, _root ) )
        return;
    if( _print_machine_readable )
    {
        std::cout << "DataWriter," << print_guid( guid ) << "," << topic_name
                  << ( discovered ? ",discovered" : ",removed" ) << std::endl;
    }
    else
    {
        std::cout << ( discovered ? "+" : "-" ) << print_guid( guid ) << " publishing topic '" << topic_name << "'"
                  << std::endl;
    }
}

void dds_sniffer::print_reader_discovered( realdds::dds_guid guid,
                                           const char * topic_name,
                                           bool discovered ) const
{
    if( filter_topic( topic_name, _root ) )
        return;
    if( _print_machine_readable )
    {
        std::cout << "DataReader," << print_guid( guid ) << "," << topic_name
                  << ( discovered ? ",discovered" : ",removed" ) << std::endl;
    }
    else
    {
        std::cout << ( discovered ? "+" : "-" ) << print_guid( guid ) << " reading topic '" << topic_name << "'"
                  << std::endl;
    }
}

void dds_sniffer::print_participant_discovered( realdds::dds_guid guid,
                                                const char * participant_name,
                                                bool discovered ) const
{
    if( _print_machine_readable )
    {
        std::cout << "Participant," << print_guid( guid ) << "," << participant_name
                  << ( discovered ? ",discovered" : ",removed" )
                  << std::endl;
    }
    else
    {
        std::cout << ( discovered ? "+" : "-" ) << "Participant '" << participant_name << "' "
                  << realdds::print_raw_guid( guid ) << std::endl;
    }
}

void dds_sniffer::print_topics_machine_readable() const
{
    std::lock_guard< std::mutex > lock( _dds_entities_lock );

    for( auto & topic : _topics_info_by_name )
    {
        if( filter_topic( topic.first, _root ) )
            continue;

        for( auto & writer : topic.second.writers )
        {
            std::cout << topic.first << ",";
            print_topic_writer( writer );
        }
        for( auto & reader : topic.second.readers )
        {
            std::cout << topic.first << ",";
            print_topic_reader( reader );
        }
    }
}

void dds_sniffer::print_topic_info( bool const is_leaf,
                                    size_t const indentation,
                                    std::string const & name,
                                    topic_info const & info,
                                    topic_display_stats const & stats,
                                    char const * prefix ) const
{
    ident( indentation, prefix );
    if( is_leaf && ! info.type_info.empty() )
        std::cout << std::setw( stats.max_indent * 4 + stats.max_len + 5 - indentation * 4 ) << std::left;
    std::cout << name;
    if( is_leaf && ! info.type_info.empty() )
        std::cout << "    " << rsutils::ios::field::group() << info.type_info;
}

void dds_sniffer::print_topics() const
{
    std::istringstream last_topic( "" );
    std::string last_topic_nested;

    std::lock_guard< std::mutex > lock( _dds_entities_lock );

    auto stats = calc_topic_display_stats();

    for( auto & topic : _topics_info_by_name )
    {
        if( filter_topic( topic.first, _root ) )
            continue;

        std::istringstream current_topic( topic.first );  // Get topic name
        std::string current_topic_nested;
        uint32_t indentation = 0;

        // Compare to previous topic
        while( std::getline( last_topic, last_topic_nested, '/' ) )  // Use / as delimiter for nested topic names
        {
            if( std::getline( current_topic, current_topic_nested, '/' ) )
            {
                if( current_topic_nested.compare( last_topic_nested ) == 0 )
                {
                    ++indentation;  // Skip parts that are same as previous topic
                }
                else
                {
                    print_topic_info( current_topic.eof(), indentation, current_topic_nested, topic.second, stats );
                    std::cout << std::endl;
                    ++indentation;
                    break;
                }
            }
        }

        // Print remainder of string
        while( std::getline( current_topic, current_topic_nested, '/' ) )
        {
            print_topic_info( current_topic.eof(), indentation, current_topic_nested, topic.second, stats );
            std::cout << std::endl;
            ++indentation;
        }

        for( auto & writer : topic.second.writers )
        {
            print_topic_writer( writer, stats.max_indent );
        }
        for( auto & reader : topic.second.readers )
        {
            print_topic_reader( reader, stats.max_indent );
        }

        last_topic.clear();
        last_topic.str( topic.first );  // Save topic name for next iteration
        last_topic.seekg( 0, last_topic.beg );
    }
}

void dds_sniffer::print_participants( bool with_topics, bool with_guids ) const
{
    for( auto & guid2name : _discovered_participants )
    {
        if( with_guids )
            std::cout << realdds::print_raw_guid_prefix( guid2name.first.guidPrefix ) << "  ";
        std::cout << guid2name.second;
        std::cout << std::endl;
        if( with_topics )
            print_topics_for( guid2name.first.guidPrefix, 1 );
    }
}


void dds_sniffer::print_topics_for( realdds::dds_guid_prefix guid_prefix, size_t indentation ) const
{
    auto stats = calc_topic_display_stats();
    stats.max_indent = indentation;  // we don't go past this

    char const * prefixes[] = { "   ", "R  ", " W ", "RW " };

    for( auto & topic : _topics_info_by_name )
    {
        if( filter_topic( topic.first, _root ) )
            continue;

        bool have_writers = false;
        for( auto & writer : topic.second.writers )
        {
            if( guid_prefix != guid_prefix.unknown() && writer.guidPrefix != guid_prefix )
                continue;
            have_writers = true;
            break;
        }
        bool have_readers = false;
        for( auto & reader : topic.second.readers )
        {
            if( guid_prefix != guid_prefix.unknown() && reader.guidPrefix != guid_prefix )
                continue;
            have_readers = true;
            break;
        }
        if( have_readers || have_writers )
        {
            char const * prefix = prefixes[have_readers + 2 * have_writers];
            print_topic_info( true, indentation, topic.first, topic.second, stats, prefix );
            std::cout << std::endl;
        }
    }
}


void dds_sniffer::ident( size_t indentation, char const * prefix ) const
{
    while( indentation > 0 )
    {
        std::cout << "    ";
        --indentation;
    }
    std::cout << prefix;
}

void dds_sniffer::print_topic_writer( realdds::dds_guid guid, size_t indentation ) const
{
    auto iter = _discovered_participants.begin();
    for( ; iter != _discovered_participants.end(); ++iter )  //_dds_entities_lock locked by caller
    {
        if( iter->first.guidPrefix == guid.guidPrefix )
        {
            if( _print_machine_readable )
            {
                std::cout << "Writer," << realdds::dds_participant::name_from_guid( iter->first ) << std::endl;
            }
            else
            {
                ident( indentation );
                std::cout << "Writer of \"" << realdds::dds_participant::name_from_guid( iter->first ) << "\"" << std::endl;
            }
            break;
        }
    }
    if( iter == _discovered_participants.end() )
    {
        ident( indentation );
        std::cout << "Writer of unknown participant" << std::endl;
    }
}


void dds_sniffer::print_topic_reader( realdds::dds_guid guid, size_t indentation ) const
{
    auto iter = _discovered_participants.begin();
    for( ; iter != _discovered_participants.end(); ++iter )  //_dds_entities_lock locked by caller
    {
        if( iter->first.guidPrefix == guid.guidPrefix )
        {
            if( _print_machine_readable )
            {
                std::cout << "Reader," << realdds::dds_participant::name_from_guid( iter->first ) << std::endl;
            }
            else
            {
                ident( indentation );
                std::cout << "Reader of \"" << realdds::dds_participant::name_from_guid( iter->first ) << "\"" << std::endl;
            }
            break;
        }
    }
    if( iter == _discovered_participants.end() )
    {
        ident( indentation );
        std::cout << "Reader of unknown participant" << std::endl;
    }
}
