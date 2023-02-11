# Internal Lib: utility
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(ipdf_utility INTERFACE)

target_include_directories(
    ipdf_utility
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# EOF
