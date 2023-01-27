add_library(utility INTERFACE)

target_include_directories(
    utility
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${spdlog_INCLUDE_DIR}
)


# EOF
