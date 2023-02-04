// **EXPERIMENTAL**
// A simple implementarion of json serializer
// vscode-style json(with comment) is preferred
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_JSON_SERIALIZER_HH
#define __IPDF_JSON_SERIALIZER_HH

#include "Singleton.hh"
#include "Token.hh"

#include <cstdint>
#include <vector>

namespace ipdf::json
{
class Serializer : public utility::Singleton<Serializer>
{
public:
    Serializer();
    ~Serializer();

    void reset();
    auto getTokens() const noexcept -> const std::vector<Token>&;
    bool tokenize(const std::string& str);

private:
    std::vector<Token> tokens_;
};
} // namespace ipdf::json

#endif // __IPDF_JSON_SERIALIZER_HH

// EOF
