// **EXPERIMENTAL**
// json serializer
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#include "Serializer.hh"

#include "Logger.hh"
#include "Token.hh"

namespace ipdf::json
{
Serializer::Serializer()
{
    reset();
}

void Serializer::reset()
{
    std::stack<Status>().swap(status_);
    tokens_.clear();
    line_   = 1;
    column_ = 0;
}

auto Serializer::getTokens() const noexcept -> const std::vector<Token>&
{
    return tokens_;
}

bool Serializer::tokenize(const std::string& str)
{
    if (str.length() == 0) return false;

    std::string strTmpBuff           = "";
    bool        shouldJumpToNextLine = false;

    // NOTE: line break should be LF, CRLF and CR are not supported
    for (const char& ch : str)
    {
        IPDF_LOG_INF("Character in ({}, {}) is {}",
                     line_,
                     column_,
                     ch == '\n' ? std::string("[line break]") : std::string("").append(1, ch));

        switch (ch)
        {
        case '\t':
            [[fallthrough]];
        case ' ':
            break;
        case '\n':
            shouldJumpToNextLine = true;
            break;
        case '{':
            tokens_.emplace_back("{", line_, column_, TokenType::BraceL);
            break;
        case '}':
            tokens_.emplace_back("}", line_, column_, TokenType::BraceR);
            break;
        case '[':
            tokens_.emplace_back("[", line_, column_, TokenType::BracketL);
            break;
        case ']':
            tokens_.emplace_back("]", line_, column_, TokenType::BracketR);
            break;
        case '"':
            tokens_.emplace_back("\"", line_, column_, TokenType::Quotation);
            break;
        case ',':
            tokens_.emplace_back(",", line_, column_, TokenType::Comma);
            break;
        case ':':
            tokens_.emplace_back(":", line_, column_, TokenType::Colon);
            break;
        case '/':
            break;
        default:
            strTmpBuff.append(1, ch);
            break;
        }

        if (shouldJumpToNextLine)
        {
            shouldJumpToNextLine = false;
            moveToNextLine();
        }
        else
        {
            moveToNextColumn();
        }
    }

    return true;
}

} // namespace ipdf::json

// EOF
