# common stream wrapper and manager. for I/O of files and other scenarios
# with experimental Unicode support, low priority.
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(stream INTERFACE)

# target_sources(
#     stream
#     PRIVATE
#         FileStream.cc
# )

target_include_directories(
    stream
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    stream
    INTERFACE
        utility
)

add_subdirectory(ut)

# EOF
