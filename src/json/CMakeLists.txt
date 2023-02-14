# Internal Lib: json(a simple implementation of json parser)
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(json STATIC)

target_sources(
    json
    PRIVATE
        Serializer.cc
)

target_include_directories(
    json
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    json
    PRIVATE
        compiler
        common
        logger
        utility
)

add_subdirectory(ut)

# EOF
