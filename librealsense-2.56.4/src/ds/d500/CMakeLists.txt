# License: Apache 2.0. See LICENSE file in root directory.
# Copyright(c) 2022 Intel Corporation. All Rights Reserved.
target_sources(${LRS_TARGET}
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/d500-device.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-color.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-motion.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-active.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-private.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-factory.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/hw_monitor_extended_buffers.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-options.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-fw-update-device.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-auto-calibration.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-debug-protocol-calibration-engine.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/d500-device.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-color.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-motion.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-active.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-private.h"
        "${CMAKE_CURRENT_LIST_DIR}/hw_monitor_extended_buffers.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-options.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-info.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-fw-update-device.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-auto-calibration.h"
        "${CMAKE_CURRENT_LIST_DIR}/d500-debug-protocol-calibration-engine.h"
)
