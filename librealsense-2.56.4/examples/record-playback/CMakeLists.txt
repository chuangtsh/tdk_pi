# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2019-2024 Intel Corporation. All Rights Reserved.
cmake_minimum_required(VERSION 3.8)

project(RealsenseExamplesRecord-Playback)

if(BUILD_GRAPHICAL_EXAMPLES)
    add_executable(rs-record-playback rs-record-playback.cpp ../example.hpp ${IMGUI_SOURCES})
    set_property(TARGET rs-record-playback PROPERTY CXX_STANDARD 11)
    target_link_libraries( rs-record-playback ${DEPENDENCIES} tclap )
    include_directories(../ ../../third-party/imgui)
    set_target_properties (rs-record-playback PROPERTIES FOLDER "Examples")
    install(TARGETS rs-record-playback RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
