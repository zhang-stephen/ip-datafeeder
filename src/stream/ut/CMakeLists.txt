# GTest for ipdf::stream
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

ipdf_create_ut(
    stream
    LIBRARIES
        stream
        ipdf_ut_entry
    SOURCES
        TestFileReadStream.cc
)

# EOF
