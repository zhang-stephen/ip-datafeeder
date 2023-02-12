// the concepts definitions for stream I/O Wrapper
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_CONCEPTS_HH
#define __IPDF_STREAM_CONCEPTS_HH

#include "Tools.hh"

#include <concepts>
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace ipdf::stream
{
template <typename T>
struct RawStreamTraits
{
    using Ch = typename T::char_type;
};

// HACK: format of concept/requires not supported completely in LLVM 15.
// clang-format off
namespace
{
template <typename _StreamT>
concept FilePointerType = requires { std::is_same_v<std::remove_cv<_StreamT*>, std::FILE*>; };

template <typename _StreamT>
concept DerivedFromInputStream = std::derived_from<_StreamT, std::basic_istream<RawStreamTraits<_StreamT>>>;

template <typename _StreamT>
concept DerivedFromOutputStream = std::derived_from<_StreamT, std::basic_ostream<RawStreamTraits<_StreamT>>>;
}

template <typename _StreamT>
concept StreamWrapperConcept = requires(_StreamT s) {
    typename _StreamT::Ch;
    { s.take() } -> std::same_as<typename _StreamT::Ch>;
    { s.peek4() } -> std::same_as<const typename _StreamT::Ch*>;
    { s.peek() } -> std::same_as<typename _StreamT::Ch>;
    { s.tell() } -> std::same_as<size_t>;
    { s.flush() } -> std::same_as<bool>;
    { s.put(typename _StreamT::Ch{}) };
    // { s.put(typename _StreamT::Ch{}, size_t{})};
    { std::invocable<decltype(&_StreamT::puts), _StreamT&, typename _StreamT::Ch, size_t> };
};

template <typename _StreamT>
concept RawInputStream = requires {
    FilePointerType<_StreamT> || DerivedFromInputStream<_StreamT>;
};

template <typename _StreamT>
concept RawOutputStream = DerivedFromOutputStream<_StreamT>;
// clang-format on

template <>
struct RawStreamTraits<std::FILE*>
{
    using Ch = char;
};

template <>
struct RawStreamTraits<int>
{
    // for Socket fd in the future
    using Ch = unsigned char;
};

template <typename _RawStreamT, typename _Traits = RawStreamTraits<_RawStreamT>>
class BasicInputStreamWrapper
{
public:
    using Ch = typename _Traits::Ch;

    BasicInputStreamWrapper(Ch* buffer, size_t bufferSize)
        : buffer_(buffer)
        , bufferSize_(bufferSize)
        , current_(buffer_)
        , count_(0)
        , readCount_(0)
        , eof_(false)
    {
        IPDF_ASSERT(bufferSize_ >= 4); // for peek4(), used to unicode checking.
        IPDF_ASSERT(buffer_ != nullptr);
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

template <typename _StreamT, typename _Traits = RawStreamTraits<_StreamT>>
class BasicOutputStreamWrapper
{
public:
    using Ch = typename _Traits::Ch;

    BasicOutputStreamWrapper(Ch* buffer, size_t bufferSize)
        : buffer_(buffer)
        , current_(buffer_)
        , bufferEnd_(buffer_ + bufferSize)
    {
        IPDF_ASSERT(buffer_ != nullptr);
    }

    BasicOutputStreamWrapper() = delete;
    // BasicOutputStreamWrapper(const BasicOutputStreamWrapper&) = delete;
    // BasicOutputStreamWrapper(BasicOutputStreamWrapper&&)      = delete;
    virtual ~BasicOutputStreamWrapper() = default;

    void put(Ch c)
    {
        if (current_ >= bufferEnd_) flush();
        *current_++ = c;
    }

    void puts(Ch c, size_t n)
    {
        auto avail = static_cast<size_t>(bufferEnd_ - current_);

        while (n > avail)
        {
            // NOTE: why not std::memset? the sizeof(Ch) may not be 1.
            for (size_t i = 0; i < avail; i++) *current_++ = c;

            flush();
            n     -= avail;
            avail = static_cast<size_t>(bufferEnd_ - current_);
        }

        if (n > 0)
        {
            for (size_t i = 0; i < n; i++) *current_++ = c;
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
