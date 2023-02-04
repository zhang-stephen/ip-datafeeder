# GTest Entry
# all internal libraries linked to ipdf_test should be named as libgt_<LIB>
# to make difference with internal libraries from src/.
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

set(IPDF_TEST_PREFIX "gt")

add_subdirectory(json)

add_executable(ipdf_test)

target_sources(
    ipdf_test
    PRIVATE
        TestMain.cc
)

target_link_libraries(
    ipdf_test
    PRIVATE
        compiler
        logger
        ${IPDF_TEST_PREFIX}_json
        GTest::GTest
        GTest::Main
)

# EOF
