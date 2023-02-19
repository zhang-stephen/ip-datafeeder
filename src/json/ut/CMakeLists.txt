# GTest for ipdf::json
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

ipdf_create_ut(
    json
    LIBRARIES
        json
        ipdf_ut_entry
    SOURCES
        TestJsonSerializer.cc
        TestJsonToken.cc
)

# EOF
