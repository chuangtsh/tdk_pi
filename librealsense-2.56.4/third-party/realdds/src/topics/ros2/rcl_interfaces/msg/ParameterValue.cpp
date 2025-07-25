// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2025 Intel Corporation. All Rights Reserved.

/*!
 * @file ParameterValue.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include <realdds/topics/ros2/rcl_interfaces/msg/ParameterValue.h>
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

rcl_interfaces::msg::ParameterValue::ParameterValue()
{
    // m_type com.eprosima.idl.parser.typecode.PrimitiveTypeCode@2b4a2ec7
    m_type = 0;
    // m_bool_value com.eprosima.idl.parser.typecode.PrimitiveTypeCode@564718df
    m_bool_value = false;
    // m_integer_value com.eprosima.idl.parser.typecode.PrimitiveTypeCode@51b7e5df
    m_integer_value = 0;
    // m_double_value com.eprosima.idl.parser.typecode.PrimitiveTypeCode@18a70f16
    m_double_value = 0.0;
    // m_string_value com.eprosima.idl.parser.typecode.StringTypeCode@62e136d3
    m_string_value ="";
    // m_byte_array_value com.eprosima.idl.parser.typecode.SequenceTypeCode@c8e4bb0

    // m_bool_array_value com.eprosima.idl.parser.typecode.SequenceTypeCode@6279cee3

    // m_integer_array_value com.eprosima.idl.parser.typecode.SequenceTypeCode@4206a205

    // m_double_array_value com.eprosima.idl.parser.typecode.SequenceTypeCode@29ba4338

    // m_string_array_value com.eprosima.idl.parser.typecode.SequenceTypeCode@57175e74


}

rcl_interfaces::msg::ParameterValue::~ParameterValue()
{










}

rcl_interfaces::msg::ParameterValue::ParameterValue(
        const ParameterValue& x)
{
    m_type = x.m_type;
    m_bool_value = x.m_bool_value;
    m_integer_value = x.m_integer_value;
    m_double_value = x.m_double_value;
    m_string_value = x.m_string_value;
    m_byte_array_value = x.m_byte_array_value;
    m_bool_array_value = x.m_bool_array_value;
    m_integer_array_value = x.m_integer_array_value;
    m_double_array_value = x.m_double_array_value;
    m_string_array_value = x.m_string_array_value;
}

rcl_interfaces::msg::ParameterValue::ParameterValue(
        ParameterValue&& x) noexcept 
{
    m_type = x.m_type;
    m_bool_value = x.m_bool_value;
    m_integer_value = x.m_integer_value;
    m_double_value = x.m_double_value;
    m_string_value = std::move(x.m_string_value);
    m_byte_array_value = std::move(x.m_byte_array_value);
    m_bool_array_value = std::move(x.m_bool_array_value);
    m_integer_array_value = std::move(x.m_integer_array_value);
    m_double_array_value = std::move(x.m_double_array_value);
    m_string_array_value = std::move(x.m_string_array_value);
}

rcl_interfaces::msg::ParameterValue& rcl_interfaces::msg::ParameterValue::operator =(
        const ParameterValue& x)
{

    m_type = x.m_type;
    m_bool_value = x.m_bool_value;
    m_integer_value = x.m_integer_value;
    m_double_value = x.m_double_value;
    m_string_value = x.m_string_value;
    m_byte_array_value = x.m_byte_array_value;
    m_bool_array_value = x.m_bool_array_value;
    m_integer_array_value = x.m_integer_array_value;
    m_double_array_value = x.m_double_array_value;
    m_string_array_value = x.m_string_array_value;

    return *this;
}

rcl_interfaces::msg::ParameterValue& rcl_interfaces::msg::ParameterValue::operator =(
        ParameterValue&& x) noexcept
{

    m_type = x.m_type;
    m_bool_value = x.m_bool_value;
    m_integer_value = x.m_integer_value;
    m_double_value = x.m_double_value;
    m_string_value = std::move(x.m_string_value);
    m_byte_array_value = std::move(x.m_byte_array_value);
    m_bool_array_value = std::move(x.m_bool_array_value);
    m_integer_array_value = std::move(x.m_integer_array_value);
    m_double_array_value = std::move(x.m_double_array_value);
    m_string_array_value = std::move(x.m_string_array_value);

    return *this;
}

bool rcl_interfaces::msg::ParameterValue::operator ==(
        const ParameterValue& x) const
{

    return (m_type == x.m_type && m_bool_value == x.m_bool_value && m_integer_value == x.m_integer_value && m_double_value == x.m_double_value && m_string_value == x.m_string_value && m_byte_array_value == x.m_byte_array_value && m_bool_array_value == x.m_bool_array_value && m_integer_array_value == x.m_integer_array_value && m_double_array_value == x.m_double_array_value && m_string_array_value == x.m_string_array_value);
}

bool rcl_interfaces::msg::ParameterValue::operator !=(
        const ParameterValue& x) const
{
    return !(*this == x);
}

size_t rcl_interfaces::msg::ParameterValue::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + 255 + 1;

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += (100 * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);



    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += (100 * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);



    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += (100 * 8) + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);



    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += (100 * 8) + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);



    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    for(size_t a = 0; a < 100; ++a)
    {
        current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + 255 + 1;
    }

    return current_alignment - initial_alignment;
}

size_t rcl_interfaces::msg::ParameterValue::getCdrSerializedSize(
        const rcl_interfaces::msg::ParameterValue& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.string_value().size() + 1;

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    if (data.byte_array_value().size() > 0)
    {
        current_alignment += (data.byte_array_value().size() * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);
    }



    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    if (data.bool_array_value().size() > 0)
    {
        current_alignment += (data.bool_array_value().size() * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);
    }



    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    if (data.integer_array_value().size() > 0)
    {
        current_alignment += (data.integer_array_value().size() * 8) + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);
    }



    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    if (data.double_array_value().size() > 0)
    {
        current_alignment += (data.double_array_value().size() * 8) + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);
    }



    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    for(size_t a = 0; a < data.string_array_value().size(); ++a)
    {
        current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) +
            data.string_array_value().at(a).size() + 1;
    }

    return current_alignment - initial_alignment;
}

void rcl_interfaces::msg::ParameterValue::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_type;
    scdr << m_bool_value;
    scdr << m_integer_value;
    scdr << m_double_value;
    scdr << m_string_value.c_str();
    scdr << m_byte_array_value;
    scdr << m_bool_array_value;
    scdr << m_integer_array_value;
    scdr << m_double_array_value;
    scdr << m_string_array_value;

}

void rcl_interfaces::msg::ParameterValue::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_type;
    dcdr >> m_bool_value;
    dcdr >> m_integer_value;
    dcdr >> m_double_value;
    dcdr >> m_string_value;
    dcdr >> m_byte_array_value;
    dcdr >> m_bool_array_value;
    dcdr >> m_integer_array_value;
    dcdr >> m_double_array_value;
    dcdr >> m_string_array_value;
}

/*!
 * @brief This function sets a value in member type
 * @param _type New value for member type
 */
void rcl_interfaces::msg::ParameterValue::type(
        uint8_t _type)
{
    m_type = _type;
}

/*!
 * @brief This function returns the value of member type
 * @return Value of member type
 */
uint8_t rcl_interfaces::msg::ParameterValue::type() const
{
    return m_type;
}

/*!
 * @brief This function returns a reference to member type
 * @return Reference to member type
 */
uint8_t& rcl_interfaces::msg::ParameterValue::type()
{
    return m_type;
}

/*!
 * @brief This function sets a value in member bool_value
 * @param _bool_value New value for member bool_value
 */
void rcl_interfaces::msg::ParameterValue::bool_value(
        bool _bool_value)
{
    m_bool_value = _bool_value;
}

/*!
 * @brief This function returns the value of member bool_value
 * @return Value of member bool_value
 */
bool rcl_interfaces::msg::ParameterValue::bool_value() const
{
    return m_bool_value;
}

/*!
 * @brief This function returns a reference to member bool_value
 * @return Reference to member bool_value
 */
bool& rcl_interfaces::msg::ParameterValue::bool_value()
{
    return m_bool_value;
}

/*!
 * @brief This function sets a value in member integer_value
 * @param _integer_value New value for member integer_value
 */
void rcl_interfaces::msg::ParameterValue::integer_value(
        int64_t _integer_value)
{
    m_integer_value = _integer_value;
}

/*!
 * @brief This function returns the value of member integer_value
 * @return Value of member integer_value
 */
int64_t rcl_interfaces::msg::ParameterValue::integer_value() const
{
    return m_integer_value;
}

/*!
 * @brief This function returns a reference to member integer_value
 * @return Reference to member integer_value
 */
int64_t& rcl_interfaces::msg::ParameterValue::integer_value()
{
    return m_integer_value;
}

/*!
 * @brief This function sets a value in member double_value
 * @param _double_value New value for member double_value
 */
void rcl_interfaces::msg::ParameterValue::double_value(
        double _double_value)
{
    m_double_value = _double_value;
}

/*!
 * @brief This function returns the value of member double_value
 * @return Value of member double_value
 */
double rcl_interfaces::msg::ParameterValue::double_value() const
{
    return m_double_value;
}

/*!
 * @brief This function returns a reference to member double_value
 * @return Reference to member double_value
 */
double& rcl_interfaces::msg::ParameterValue::double_value()
{
    return m_double_value;
}

/*!
 * @brief This function copies the value in member string_value
 * @param _string_value New value to be copied in member string_value
 */
void rcl_interfaces::msg::ParameterValue::string_value(
        const std::string& _string_value)
{
    m_string_value = _string_value;
}

/*!
 * @brief This function moves the value in member string_value
 * @param _string_value New value to be moved in member string_value
 */
void rcl_interfaces::msg::ParameterValue::string_value(
        std::string&& _string_value)
{
    m_string_value = std::move(_string_value);
}

/*!
 * @brief This function returns a constant reference to member string_value
 * @return Constant reference to member string_value
 */
const std::string& rcl_interfaces::msg::ParameterValue::string_value() const
{
    return m_string_value;
}

/*!
 * @brief This function returns a reference to member string_value
 * @return Reference to member string_value
 */
std::string& rcl_interfaces::msg::ParameterValue::string_value()
{
    return m_string_value;
}
/*!
 * @brief This function copies the value in member byte_array_value
 * @param _byte_array_value New value to be copied in member byte_array_value
 */
void rcl_interfaces::msg::ParameterValue::byte_array_value(
        const std::vector<uint8_t>& _byte_array_value)
{
    m_byte_array_value = _byte_array_value;
}

/*!
 * @brief This function moves the value in member byte_array_value
 * @param _byte_array_value New value to be moved in member byte_array_value
 */
void rcl_interfaces::msg::ParameterValue::byte_array_value(
        std::vector<uint8_t>&& _byte_array_value)
{
    m_byte_array_value = std::move(_byte_array_value);
}

/*!
 * @brief This function returns a constant reference to member byte_array_value
 * @return Constant reference to member byte_array_value
 */
const std::vector<uint8_t>& rcl_interfaces::msg::ParameterValue::byte_array_value() const
{
    return m_byte_array_value;
}

/*!
 * @brief This function returns a reference to member byte_array_value
 * @return Reference to member byte_array_value
 */
std::vector<uint8_t>& rcl_interfaces::msg::ParameterValue::byte_array_value()
{
    return m_byte_array_value;
}
/*!
 * @brief This function copies the value in member bool_array_value
 * @param _bool_array_value New value to be copied in member bool_array_value
 */
void rcl_interfaces::msg::ParameterValue::bool_array_value(
        const std::vector<bool>& _bool_array_value)
{
    m_bool_array_value = _bool_array_value;
}

/*!
 * @brief This function moves the value in member bool_array_value
 * @param _bool_array_value New value to be moved in member bool_array_value
 */
void rcl_interfaces::msg::ParameterValue::bool_array_value(
        std::vector<bool>&& _bool_array_value)
{
    m_bool_array_value = std::move(_bool_array_value);
}

/*!
 * @brief This function returns a constant reference to member bool_array_value
 * @return Constant reference to member bool_array_value
 */
const std::vector<bool>& rcl_interfaces::msg::ParameterValue::bool_array_value() const
{
    return m_bool_array_value;
}

/*!
 * @brief This function returns a reference to member bool_array_value
 * @return Reference to member bool_array_value
 */
std::vector<bool>& rcl_interfaces::msg::ParameterValue::bool_array_value()
{
    return m_bool_array_value;
}
/*!
 * @brief This function copies the value in member integer_array_value
 * @param _integer_array_value New value to be copied in member integer_array_value
 */
void rcl_interfaces::msg::ParameterValue::integer_array_value(
        const std::vector<int64_t>& _integer_array_value)
{
    m_integer_array_value = _integer_array_value;
}

/*!
 * @brief This function moves the value in member integer_array_value
 * @param _integer_array_value New value to be moved in member integer_array_value
 */
void rcl_interfaces::msg::ParameterValue::integer_array_value(
        std::vector<int64_t>&& _integer_array_value)
{
    m_integer_array_value = std::move(_integer_array_value);
}

/*!
 * @brief This function returns a constant reference to member integer_array_value
 * @return Constant reference to member integer_array_value
 */
const std::vector<int64_t>& rcl_interfaces::msg::ParameterValue::integer_array_value() const
{
    return m_integer_array_value;
}

/*!
 * @brief This function returns a reference to member integer_array_value
 * @return Reference to member integer_array_value
 */
std::vector<int64_t>& rcl_interfaces::msg::ParameterValue::integer_array_value()
{
    return m_integer_array_value;
}
/*!
 * @brief This function copies the value in member double_array_value
 * @param _double_array_value New value to be copied in member double_array_value
 */
void rcl_interfaces::msg::ParameterValue::double_array_value(
        const std::vector<double>& _double_array_value)
{
    m_double_array_value = _double_array_value;
}

/*!
 * @brief This function moves the value in member double_array_value
 * @param _double_array_value New value to be moved in member double_array_value
 */
void rcl_interfaces::msg::ParameterValue::double_array_value(
        std::vector<double>&& _double_array_value)
{
    m_double_array_value = std::move(_double_array_value);
}

/*!
 * @brief This function returns a constant reference to member double_array_value
 * @return Constant reference to member double_array_value
 */
const std::vector<double>& rcl_interfaces::msg::ParameterValue::double_array_value() const
{
    return m_double_array_value;
}

/*!
 * @brief This function returns a reference to member double_array_value
 * @return Reference to member double_array_value
 */
std::vector<double>& rcl_interfaces::msg::ParameterValue::double_array_value()
{
    return m_double_array_value;
}
/*!
 * @brief This function copies the value in member string_array_value
 * @param _string_array_value New value to be copied in member string_array_value
 */
void rcl_interfaces::msg::ParameterValue::string_array_value(
        const std::vector<std::string>& _string_array_value)
{
    m_string_array_value = _string_array_value;
}

/*!
 * @brief This function moves the value in member string_array_value
 * @param _string_array_value New value to be moved in member string_array_value
 */
void rcl_interfaces::msg::ParameterValue::string_array_value(
        std::vector<std::string>&& _string_array_value)
{
    m_string_array_value = std::move(_string_array_value);
}

/*!
 * @brief This function returns a constant reference to member string_array_value
 * @return Constant reference to member string_array_value
 */
const std::vector<std::string>& rcl_interfaces::msg::ParameterValue::string_array_value() const
{
    return m_string_array_value;
}

/*!
 * @brief This function returns a reference to member string_array_value
 * @return Reference to member string_array_value
 */
std::vector<std::string>& rcl_interfaces::msg::ParameterValue::string_array_value()
{
    return m_string_array_value;
}

size_t rcl_interfaces::msg::ParameterValue::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    size_t current_align = current_alignment;













    return current_align;
}

bool rcl_interfaces::msg::ParameterValue::isKeyDefined()
{
    return false;
}

void rcl_interfaces::msg::ParameterValue::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
              
}


