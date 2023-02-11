# common stream wrapper and manager. for I/O of files and other scenarios
# with experimental Unicode support, low priority.
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(ipdf_stream STATIC)

target_sources(
    ipdf_stream
    PRIVATE
        FileStream.cc
)

target_include_directories(
    ipdf_stream
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ipdf_stream
    PRIVATE
        utility
)

# EOF
