// utilities for stream testing
// Copyright(c) Stephen Zhang 2023. All Right Reserved.

#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include <random>
#include <tuple>

namespace ipdf::test
{
namespace details
{
inline auto randomIntGenerator(int left, int right) -> std::tuple<std::mt19937, std::uniform_int_distribution<>>
{
    auto rd = std::random_device();
    return { std::mt19937(rd()), std::uniform_int_distribution<>(left, right) };
}
} // namespace details

template <typename It>
inline void generateContents(It begin, It end, int left, int right)
{
    auto [seed, generator] = details::randomIntGenerator(left, right);
    // NOTE: C++ cannot capture structual binding objs, see
    // https://burnicki.pl/en/2021/04/19/capture-structured-bindings.html
    std::generate(begin, end, [&gen = generator, &s = seed] { return gen(s); });
}

} // namespace ipdf::test

// EOF
