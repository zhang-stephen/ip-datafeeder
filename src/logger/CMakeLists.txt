# Logger module for ip-datafeeder
# A wrapper and some initialization for spdlog
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(ipdf_logger STATIC)

target_sources(
    ipdf_logger
    PRIVATE
        Logger.cc
)

target_include_directories(
    ipdf_logger
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ipdf_logger
    PUBLIC
        spdlog::spdlog_header_only
    PRIVATE
        compiler
        ipdf_utility
        fmt::fmt
)

# EOF
