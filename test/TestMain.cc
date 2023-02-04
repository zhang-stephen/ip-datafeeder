// GTest Entry
// all TEST should be put into namespace ipdf::test
// Copyright(c) Stephen Zhang 2023. All Right Reserved.

#include "Logger.hh"

#include <gtest/gtest.h>

int main(int c, char** v)
{
    ipdf::logger::setupSpdLog();
    ::testing::InitGoogleTest(&c, v);

    return RUN_ALL_TESTS();
}
