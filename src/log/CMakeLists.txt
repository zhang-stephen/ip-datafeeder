# Library for common logging
# packaging from boost::log v2

add_library(logging STATIC)

target_include_directories(
    logging
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    logging
    PRIVATE
        log.cc
)

target_compile_definitions(
    logging
    PUBLIC
        BOOST_LOG_DYN_LINK
)

target_link_libraries(
    logging
    PUBLIC
        compiler_conf
        boost_log_setup-mt
        boost_log-mt
        boost_thread-mt
        boost_date_time-mt
)

# EOF