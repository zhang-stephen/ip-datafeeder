// **EXPERIMENTAL**
// A simple implementarion of json serializer
// vscode-style json(with comment) is preferred
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

#include "Singleton.hh"
#include "Token.hh"

#include <cstdint>
#include <stack>
#include <vector>

namespace ipdf::json
{
class Serializer : public utility::Singleton<Serializer>
{
public:
    Serializer();
    ~Serializer() override = default;

    void reset();
    auto getTokens() const noexcept -> const std::vector<Token>&;
    bool tokenize(const std::string& str);

private:
    enum class Status : uint8_t
    {
        Normal,
        InQuotationMarks,
        InLineComment,
        ValidString,
    };

    void moveToNextColumn()
    {
        column_++;
    }

    void moveToNextLine()
    {
        line_++;
        column_ = 0;
    }

    void updateStatus(const Status& status)
    {
        if (status_.top() != status)
        {
            status_.push(status);
        }
        else
        {
            status_.pop();
        }
    }

    std::stack<Status> status_;
    std::vector<Token> tokens_;
    size_t             line_;
    size_t             column_;
};
} // namespace ipdf::json

// EOF
