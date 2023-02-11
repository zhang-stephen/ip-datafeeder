# Internal Lib: json(a simple implementation of json parser)
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(ipdf_json STATIC)

target_sources(
    ipdf_json
    PRIVATE
        Serializer.cc
)

target_include_directories(
    ipdf_json
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ipdf_json
    PRIVATE
        compiler
        ipdf_common
        ipdf_logger
        ipdf_utility
)

add_subdirectory(ut)

# EOF
