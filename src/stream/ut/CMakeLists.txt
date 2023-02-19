# GTest for ipdf::stream
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

set(UT_MODULE_NAME  ${IPDF_UT_PREFIX}_stream)

message(STATUS "creating ut -> ${UT_MODULE_NAME}")

add_executable(${UT_MODULE_NAME})

target_sources(
    ${UT_MODULE_NAME}
    PRIVATE
        TestFileReadStream.cc
)

target_link_libraries(
    ${UT_MODULE_NAME}
    PRIVATE
        logger
        stream
        ipdf_ut_entry
)

add_test(
    NAME ${UT_MODULE_NAME}
    COMMAND $<TARGET_FILE:${UT_MODULE_NAME}>
)

# EOF
