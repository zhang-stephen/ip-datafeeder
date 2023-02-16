// the concepts definitions for stream I/O Wrapper
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

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
    using Ch         = uint8_t;
    using StreamType = int;
};

// HACK: format of concept/requires not supported completely in LLVM 15.
// clang-format off
namespace
{
template <typename StreamT>
concept FilePointerType = std::same_as<StreamT, std::FILE*>;

template <typename StreamT>
concept DerivedFromStdInputStream = std::derived_from<StreamT, std::basic_istream<RawStreamCharType<StreamT>>>;

template <typename StreamT>
concept DerivedFromStdOutputStream = std::derived_from<StreamT, std::basic_ostream<RawStreamCharType<StreamT>>>;
} // namespace

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

template <typename StreamT>
concept RawInputStream = FilePointerType<StreamT> || DerivedFromStdInputStream<StreamT>;

template <typename StreamT>
concept RawOutputStream = FilePointerType<StreamT> || DerivedFromStdOutputStream<StreamT>;

template<typename StreamT>
concept RawIoStream = RawInputStream<StreamT> && RawOutputStream<StreamT>;
// clang-format on

template <typename RawStreamT, typename Traits = RawStreamTraits<RawStreamT>>
class BasicInputStreamWrapper
{
public:
    using StreamType = typename Traits::StreamType;
    using Ch         = typename Traits::Ch;

    BasicInputStreamWrapper(StreamType stream, Ch* buffer, size_t bufferSize)
        : stream_(stream)
        , bufferSize_(bufferSize)
        , count_(0)
        , readCount_(0)
        , buffer_(buffer)
        , bufferLast_(nullptr)
        , current_(buffer_)
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

template <typename StreamT, typename Traits = RawStreamTraits<StreamT>>
class BasicOutputStreamWrapper
{
public:
    using StreamType = typename Traits::StreamType;
    using Ch         = typename Traits::Ch;

    BasicOutputStreamWrapper(StreamType stream, Ch* buffer, size_t bufferSize)
        : stream_(stream)
        , buffer_(buffer)
        , bufferEnd_(buffer_ + bufferSize)
        , current_(buffer_)
    {
    }

    BasicOutputStreamWrapper() = delete;
    // BasicOutputStreamWrapper(const BasicOutputStreamWrapper&) = delete;
    // BasicOutputStreamWrapper(BasicOutputStreamWrapper&&)      = delete;
    virtual ~BasicOutputStreamWrapper() = default;

    virtual void put(Ch)            = 0;
    virtual void puts(Ch, size_t)   = 0;
    virtual void write(Ch*, size_t) = 0;
    virtual bool flush()            = 0;

protected:
    StreamType stream_;
    Ch*        buffer_;
    Ch*        bufferEnd_;
    Ch*        current_;
};

template <typename StreamT, typename Traits = RawStreamTraits<StreamT>>
class BasicIoStreamWrapper : virtual public BasicInputStreamWrapper<StreamT>,
                             virtual public BasicOutputStreamWrapper<StreamT>
{
public:
    using StreamType = typename Traits::StreamType;
    using Ch         = typename Traits::Ch;

    BasicIoStreamWrapper(StreamType stream, Ch* buffer, size_t bufferSize)
        : BasicInputStreamWrapper<StreamT>(stream, buffer, bufferSize)
        , BasicOutputStreamWrapper<StreamT>(stream, buffer, bufferSize)
    {
    }

    BasicIoStreamWrapper()  = delete;
    ~BasicIoStreamWrapper() = default;
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

// EOF
