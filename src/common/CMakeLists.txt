# Common Lib for ip-Datafeeder
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(ipdf_common INTERFACE)

target_include_directories(
    ipdf_common
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# EOF
