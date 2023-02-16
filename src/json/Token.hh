// **EXPERIMENTAL**
// definitions of token in json string
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <tuple>

namespace ipdf::json
{
enum class TokenType : uint8_t
{
    Null, // null
    Integer, // int
    Float, // float
    Boolean, // true/false
    String, // "..."
    BracketL, // [
    BracketR, // ]
    BraceL, // {
    BraceR, // }
    Comma, // ,
    Quotation, // "
    Colon, // :
};

class Token final
{
public:
    // NOTE: constexpr std::string is supported in C++20
    constexpr Token(std::string token, size_t line, size_t column, TokenType type)
        : line_(line)
        , column_(column)
        , token_(token)
        , type_(type)
    {
    }
    ~Token()
    {
        line_ = column_ = 0;
        token_.clear();
    }

    Token()             = delete;
    Token(const Token&) = default;
    Token(Token&&)      = default;

    auto position() const noexcept -> const std::tuple<size_t, size_t>
    {
        return { line_, column_ };
    }

    TokenType type() const noexcept
    {
        return type_;
    }

    const std::string& token() const noexcept
    {
        return token_;
    }

    size_t length() const noexcept
    {
        return token_.length();
    }

private:
    size_t      line_;
    size_t      column_;
    std::string token_;
    TokenType   type_;
};
} // namespace ipdf::json

// EOF
