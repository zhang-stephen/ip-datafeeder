# Logger module for ip-datafeeder
# A wrapper and some initialization for spdlog
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(logger STATIC)

target_sources(
    logger
    PRIVATE
        Logger.cc
)

target_include_directories(
    logger
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    logger
    PUBLIC
        spdlog::spdlog_header_only
    PRIVATE
        compiler
        utility
        fmt::fmt
)

# EOF
