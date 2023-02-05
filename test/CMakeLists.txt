# GTest Entry
# all internal libraries linked to ipdf_test should be named as libgt_<LIB>
# to make difference with internal libraries from src/.
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

include(CTest)

set(IPDF_TEST_POSTFIX "ut")
add_library(ipdf_ut_entry STATIC)

target_sources(
    ipdf_ut_entry
    PRIVATE
        TestMain.cc
)

target_link_libraries(
    ipdf_ut_entry
    PUBLIC
        compiler
        common
        logger
        utility
)

add_subdirectory(json)

# EOF
