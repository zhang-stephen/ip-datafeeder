# GTest for ipdf::json
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

add_library(${IPDF_TEST_PREFIX}_json STATIC)

target_sources(
    ${IPDF_TEST_PREFIX}_json
    PRIVATE
        TestJsonToken.cc
)

target_link_libraries(
    ${IPDF_TEST_PREFIX}_json
    PRIVATE
        compiler
        json
        GTest::GTest
)

# EOF
