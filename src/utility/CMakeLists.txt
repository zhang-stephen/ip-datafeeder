# Internal Lib: utility
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(utility INTERFACE)

target_include_directories(
    utility
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${spdlog_INCLUDE_DIR}
)


# EOF
