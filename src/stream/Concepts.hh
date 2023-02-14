// the concepts definitions for stream I/O Wrapper
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_CONCEPTS_HH
#define __IPDF_STREAM_CONCEPTS_HH

#include "Tools.hh"

#include <concepts>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <type_traits>

namespace ipdf::stream
{
template <typename T>
struct RawStreamTraits
{
    using Ch         = typename T::char_type;
    using StreamType = T&;
};

template <typename T>
using RawStreamCharType = typename RawStreamTraits<T>::Ch;

template <>
struct RawStreamTraits<std::FILE*>
{
    using Ch         = char;
    using StreamType = std::FILE*;
};

template <>
struct RawStreamTraits<int>
{
    // for Socket fd in the future
    using Ch         = unsigned char;
    using StreamType = int;
};

// HACK: format of concept/requires not supported completely in LLVM 15.
// clang-format off
namespace
{
template <typename _StreamT>
concept FilePointerType = std::same_as<_StreamT, std::FILE*>;

template <typename _StreamT>
concept DerivedFromStdInputStream = std::derived_from<_StreamT, std::basic_istream<RawStreamCharType<_StreamT>>>;

template <typename _StreamT>
concept DerivedFromStdOutputStream = std::derived_from<_StreamT, std::basic_ostream<RawStreamCharType<_StreamT>>>;
}

// template <typename _StreamT>
// concept StreamWrapperConcept = requires(_StreamT s) {
//     typename _StreamT::Ch;
//     { s.take() } -> std::same_as<typename _StreamT::Ch>;
//     { s.peek4() } -> std::same_as<const typename _StreamT::Ch*>;
//     { s.peek() } -> std::same_as<typename _StreamT::Ch>;
//     { s.tell() } -> std::same_as<size_t>;
//     { s.flush() } -> std::same_as<bool>;
//     { s.put(typename _StreamT::Ch{}) };
//     // { s.put(typename _StreamT::Ch{}, size_t{})};
//     { std::invocable<decltype(&_StreamT::puts), _StreamT&, typename _StreamT::Ch, size_t> };
// };

template <typename _StreamT>
concept RawInputStream = FilePointerType<_StreamT> || DerivedFromStdInputStream<_StreamT>;

template <typename _StreamT>
concept RawOutputStream = FilePointerType<_StreamT> || DerivedFromStdOutputStream<_StreamT>;

template<typename _StreamT>
concept RawIoStream = RawInputStream<_StreamT> && RawOutputStream<_StreamT>;
// clang-format on

template <typename _RawStreamT, typename _Traits = RawStreamTraits<_RawStreamT>>
class BasicInputStreamWrapper
{
public:
    using StreamType = typename _Traits::StreamType;
    using Ch         = typename _Traits::Ch;

    BasicInputStreamWrapper(StreamType stream, Ch* buffer, size_t bufferSize)
        : stream_(stream)
        , buffer_(buffer)
        , bufferSize_(bufferSize)
        , current_(buffer_)
        , count_(0)
        , readCount_(0)
        , eof_(false)
    {
        IPDF_ASSERT(bufferSize_ >= 4); // for peek4(), used to unicode checking.
        IPDF_ASSERT(buffer_ != nullptr);
    }

    BasicInputStreamWrapper()  = delete;
    ~BasicInputStreamWrapper() = default;

    const Ch* peek4() { return (current_ + 4 - !eof_ <= bufferLast_) ? current_ : nullptr; }
    Ch        peek() { return *current_; }
    size_t    tell() { return count_ + static_cast<size_t>(current_ - buffer_); }
    Ch        take()
    {
        Ch c = *current_;
        read();
        return c;
    }

protected:
    virtual void read() = 0;

    StreamType stream_;
    size_t     bufferSize_;
    size_t     count_;
    size_t     readCount_;
    Ch*        buffer_;
    Ch*        bufferLast_;
    Ch*        current_;
    bool       eof_;
};

template <typename _StreamT, typename _Traits = RawStreamTraits<_StreamT>>
class BasicOutputStreamWrapper
{
public:
    using StreamType = typename _Traits::StreamType;
    using Ch         = typename _Traits::Ch;

    BasicOutputStreamWrapper(StreamType stream, Ch* buffer, size_t bufferSize)
        : stream_(stream)
        , buffer_(buffer)
        , current_(buffer_)
        , bufferEnd_(buffer_ + bufferSize)
    {
    }

    BasicOutputStreamWrapper() = delete;
    // BasicOutputStreamWrapper(const BasicOutputStreamWrapper&) = delete;
    // BasicOutputStreamWrapper(BasicOutputStreamWrapper&&)      = delete;
    virtual ~BasicOutputStreamWrapper() = default;

    virtual void put(Ch)          = 0;
    virtual void puts(Ch, size_t) = 0;
    virtual bool flush()          = 0;

protected:
    StreamType stream_;
    Ch*        buffer_;
    Ch*        bufferEnd_;
    Ch*        current_;
};

// check for raw streams
static_assert(RawInputStream<std::istream>);
static_assert(RawInputStream<std::wistream>);
static_assert(RawInputStream<std::ifstream>);
static_assert(RawInputStream<std::wifstream>);
static_assert(RawInputStream<std::istringstream>);
static_assert(RawInputStream<std::wistringstream>);
static_assert(RawOutputStream<std::ostream>);
static_assert(RawOutputStream<std::wostream>);
static_assert(RawOutputStream<std::ofstream>);
static_assert(RawOutputStream<std::wofstream>);
static_assert(RawOutputStream<std::ostringstream>);
static_assert(RawOutputStream<std::wostringstream>);
static_assert(RawIoStream<std::iostream>);
static_assert(RawIoStream<std::wiostream>);
static_assert(RawIoStream<std::fstream>);
static_assert(RawIoStream<std::wfstream>);
static_assert(RawIoStream<std::stringstream>);
static_assert(RawIoStream<std::wstringstream>);
} // namespace ipdf::stream

#endif // __IPDF_STREAM_CONCEPTS_HH

// EOF
