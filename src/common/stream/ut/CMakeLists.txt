# GTest for ipdf::stream
# Copyright (c) Stephen Zhang 2023. All Right Reserved.

ipdf_create_ut(
    stream
    LIBRARIES
        stream
        ipdf_ut_entry
    SOURCES
        TestFileReadStream.cc
        TestIoStream.cc
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# EOF
