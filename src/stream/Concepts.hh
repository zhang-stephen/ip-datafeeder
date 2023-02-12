// the concepts definitions for stream I/O Wrapper
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_CONCEPTS_HH
#define __IPDF_STREAM_CONCEPTS_HH

#include <concepts>
#include <cstdint>
#include <iostream>
#include <type_traits>

#include "Tools.hh"

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

template <typename _StreamT, typename _CharT = char>
class BasicInputStreamWrapper
{
public:
    using Ch = _CharT;

    BasicInputStreamWrapper(Ch* buffer, size_t bufferSize)
        : buffer_(buffer)
        , bufferSize_(bufferSize)
        , current_(buffer_)
        , count_(0)
        , readCount_(0)
        , eof_(false)
    {
        IPDF_ASSERT(bufferSize_ >= 4); // for peek4(), used to unicode checking.
        read();
    }

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

    size_t bufferSize_;
    size_t count_;
    size_t readCount_;
    Ch*    buffer_;
    Ch*    bufferLast_;
    Ch*    current_;
    bool   eof_;
};

template <typename _StreamT, typename _CharT = char>
class BasicOutputStreamWrapper
{
public:
    using Ch = _CharT;

    BasicOutputStreamWrapper(Ch* buffer, size_t bufferSize) {}

    BasicOutputStreamWrapper() = delete;
    BasicOutputStreamWrapper(const BasicOutputStreamWrapper&) = delete;
    BasicOutputStreamWrapper(BasicOutputStreamWrapper&&)      = delete;
    virtual ~BasicOutputStreamWrapper()                        = default;

    void put(Ch c)
    {
        if (current_ >= bufferEnd_) flush();
        *current_++ = c;
    }

    void put(Ch c, size_t n) 
    {
        auto avail = static_cast<size_t>(bufferEnd_ - current_);

        while (n > avail)
        {
            std::memset(current_, c, avail);
            current_ += avail;
            flush();
            n     -= avail;
            avail = static_cast<size_t>(bufferEnd_ - current_);
        }

        if (n > 0)
        {
            std::memset(current_, c, n);
            current_ += n;
        }
    }

    virtual bool flush() = 0;

protected:
    Ch* buffer_;
    Ch* bufferEnd_;
    Ch* current_;
};
} // namespace ipdf::stream

#endif // __IPDF_STREAM_CONCEPTS_HH

// EOF
