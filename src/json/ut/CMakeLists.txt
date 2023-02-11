# GTest for ipdf::json
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

set(UT_MODULE_NAME json_ut)

message(STATUS "building ut -> ${UT_MODULE_NAME}")

add_executable(${UT_MODULE_NAME})

target_sources(
    ${UT_MODULE_NAME}
    PRIVATE
        TestJsonSerializer.cc
        TestJsonToken.cc
)

target_link_libraries(
    ${UT_MODULE_NAME}
    PRIVATE
        ipdf_json
        ipdf_ut_entry
)

add_test(
    NAME ipdf_${UT_MODULE_NAME}
    COMMAND $<TARGET_FILE:${UT_MODULE_NAME}>
)

# EOF
