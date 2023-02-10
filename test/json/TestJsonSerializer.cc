// GTest Entry of json serializer
// Copyright(c) Stephen Zhang 2023. All Right Reserved.

#include "Serializer.hh"

#include <gtest/gtest.h>

namespace ipdf::test
{
class JsonSerializerTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}

public:
    static inline std::string jsonString =
R"({
    "Key1": 1,
    "Key2": [
        {
            "Key3": true,
            "Key4": 1.0,
            "Key5": null
        }
    ]
})";
};

TEST_F(JsonSerializerTest, InitialJsonString)
{
    auto& serializer = ipdf::json::Serializer::instance();

    serializer.reset();

    // clang-format off

    // clang-format on

    ASSERT_TRUE(serializer.tokenize(jsonString));
}

} // namespace ipdf::test

// EOF
