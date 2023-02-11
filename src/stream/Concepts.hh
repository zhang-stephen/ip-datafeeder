// the concepts definitions for stream I/O Wrapper
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_CONCEPTS_HH
#define __IPDF_STREAM_CONCEPTS_HH

#include <concepts>
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace ipdf::stream
{
// HACK: format of concept/requires not supported completely in LLVM 15.
// clang-format off
namespace
{
template <typename _StreamT>
concept FilePointerType = requires { std::is_same_v<std::remove_cv<_StreamT*>, std::FILE*>; };

template <typename _StreamT, typename _CharT>
concept DerivedFromInputStream = std::derived_from<_StreamT, std::basic_istream<_CharT>>;

template <typename _StreamT, typename _CharT>
concept DerivedFromOutputStream =  std::derived_from<_StreamT, std::basic_ostream<_CharT>>;
}

template <typename _StreamT>
concept StreamWrapper = requires(_StreamT s) {
    typename _StreamT::Ch;
    { s.take() } -> std::same_as<typename _StreamT::Ch>;
    { s.peek4() } -> std::same_as<const typename _StreamT::Ch*>;
    { s.peek() } -> std::same_as<typename _StreamT::Ch>;
    { s.tell() } -> std::same_as<size_t>;
    { s.put(typename _StreamT::Ch{}) };
    { s.put(typename _StreamT::Ch{}, size_t{})};
    { s.flush() };
};

template <typename _StreamT, typename _CharT = char>
concept RawInputStream = requires {
    FilePointerType<_StreamT> || DerivedFromInputStream<_StreamT, _CharT>;
};

template <typename _StreamT, typename _CharT = char>
concept RawOutputStream = DerivedFromOutputStream<_StreamT, _CharT>;
// clang-format on
} // namespace ipdf::stream

#endif // __IPDF_STREAM_CONCEPTS_HH

// EOF
