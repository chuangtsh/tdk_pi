# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2019-2024 Intel Corporation. All Rights Reserved.
cmake_minimum_required(VERSION 3.8)

project(RealsenseExamplesPost-Processing)

if(BUILD_GRAPHICAL_EXAMPLES)
    add_executable(rs-post-processing rs-post-processing.cpp ../example.hpp ${IMGUI_SOURCES})
    set_property(TARGET rs-post-processing PROPERTY CXX_STANDARD 11)
    target_link_libraries( rs-post-processing ${DEPENDENCIES} tclap )
    include_directories(../ ../../third-party/imgui)
    set_target_properties (rs-post-processing PROPERTIES FOLDER "Examples")
    install(TARGETS rs-post-processing RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
