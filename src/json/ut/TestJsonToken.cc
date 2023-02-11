// GTest Entry of json tokens
// Copyright(c) Stephen Zhang 2023. All Right Reserved.

#include "Token.hh"

#include <gtest/gtest.h>
#include <vector>

namespace ipdf::test
{
using ipdf::json::Token;
using ipdf::json::TokenType;

class JsonTokenTest : public ::testing::Test
{
public:
    void SetUp() override {}
    void TearDown() override {}

    inline static std::vector<Token> rights_ = {
        Token("null", 1, 0, TokenType::Null),     Token("123", 2, 0, TokenType::Integer),
        Token("1.0", 3, 17, TokenType::Float),    Token("true", 4, 12, TokenType::Boolean),
        Token("string", 4, 2, TokenType::String), Token("[", 5, 0, TokenType::BracketL),
        Token("]", 6, 0, TokenType::BracketR),    Token("{", 5, 0, TokenType::BraceL),
        Token("}", 6, 0, TokenType::BraceR),      Token(",", 7, 20, TokenType::Comma),
        Token("\"", 7, 39, TokenType::Quotation), Token(":", 8, 22, TokenType::Colon),
    };

    inline static std::vector<Token> mistakes_ = {
        Token("string", 0, 1, TokenType::String), // line number should be greater than zero
    };

    static constexpr size_t expectedRightCnt_ = 12;
};

TEST_F(JsonTokenTest, Tokens)
{
    const std::string tokenStrings[] = {
        "null", "123", "1.0", "true", "string", "[", "]", "{", "}", ",", "\"", ":",
    };

    for (size_t i = 0; i < rights_.size(); i++)
    {
        auto& token = rights_.at(i).token();
        EXPECT_STREQ(tokenStrings[i].c_str(), token.c_str());
    }
}

TEST_F(JsonTokenTest, TokenTypes)
{
    constexpr TokenType types[] = {
        TokenType::Null,   TokenType::Integer,  TokenType::Float,     TokenType::Boolean,
        TokenType::String, TokenType::BracketL, TokenType::BracketR,  TokenType::BraceL,
        TokenType::BraceR, TokenType::Comma,    TokenType::Quotation, TokenType::Colon,
    };

    for (size_t i = 0; i < rights_.size(); i++)
    {
        auto type = rights_.at(i).type();
        EXPECT_EQ(type, types[i]);
    }
}

TEST_F(JsonTokenTest, Positions)
{
    constexpr size_t lines[] = {
        1, 2, 3, 4, 4, 5, 6, 5, 6, 7, 7, 8,
    };

    constexpr size_t columns[] = {
        0, 0, 17, 12, 2, 0, 0, 0, 0, 20, 39, 22,
    };

    for (size_t i = 0; i < rights_.size(); i++)
    {
        auto [line, column] = rights_.at(i).position();
        EXPECT_EQ(line, lines[i]);
        EXPECT_EQ(column, columns[i]);
    }
}

TEST_F(JsonTokenTest, FalseLineNumber)
{
    auto [line, _] = mistakes_[0].position();
    EXPECT_FALSE(line > 0);
}
} // namespace ipdf::test

// EOF
