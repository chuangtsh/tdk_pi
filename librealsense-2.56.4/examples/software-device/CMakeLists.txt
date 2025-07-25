# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2019-2024 Intel Corporation. All Rights Reserved.
cmake_minimum_required(VERSION 3.8)

project(RealsenseExamplesSoftwareDevice)

# Save the command line compile commands in the build output
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(BUILD_GRAPHICAL_EXAMPLES)
    add_executable(rs-software-device rs-software-device.cpp ${IMGUI_SOURCES})
    set_property(TARGET rs-software-device PROPERTY CXX_STANDARD 11)
    target_link_libraries( rs-software-device ${DEPENDENCIES} tclap )
    include_directories(../ ../../third-party/ ../../common/res)
    set_target_properties (rs-software-device PROPERTIES FOLDER "Examples")
    install(TARGETS rs-software-device RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
