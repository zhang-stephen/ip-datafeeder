// I/O stream wrapper for STL streams:
//      - istream, ifstream, wistream, wifstream
//      - ostream, ofstream, wostream, wofstream
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_IO_STREAM_HH
#define __IPDF_STREAM_IO_STREAM_HH

#include "Concepts.hh"

namespace ipdf::stream
{
template <RawInputStream _StreamT>
class InputStreamWrapper : public BasicInputStreamWrapper<_StreamT>
{
public:
    using StreamType = _StreamT;
    using Ch         = typename BasicOutputStreamWrapper<_StreamT>::Ch;

    InputStreamWrapper(StreamType& is, Ch* buffer, size_t bufferSize)
        : is_(is)
        , BasicInputStreamWrapper<_StreamT>(buffer, bufferSize)
    {
        read();
    }

    // not implemented
    void put(Ch) { IPDF_ASSERT(false); }
    void puts(Ch) { IPDF_ASSERT(false); }
    bool flush() { IPDF_ASSERT(false); }

private:
    void read() override {}

    StreamType& is_;
};

template <RawOutputStream _StreamT>
class OutputStreamWrapper : public BasicOutputStreamWrapper<_StreamT>
{
public:
    using StreamType = _StreamT;
    using Ch         = typename BasicOutputStreamWrapper<_StreamT>::Ch;

    OutputStreamWrapper(StreamType& os, Ch* buffer, size_t bufferSize)
        : os_(os)
        , BasicOutputStreamWrapper<_StreamT>(buffer, bufferSize)
    {
    }

    bool flush() {}

    // not implemented
    Ch        peek() { IPDF_ASSERT(false); }
    Ch        take() { IPDF_ASSERT(false); }
    const Ch* peek4() { IPDF_ASSERT(false); }
    size_t    tell() { IPDF_ASSERT(false); }

private:
    StreamType& os_;
};

static_assert(StreamWrapperConcept<InputStreamWrapper<std::istream>>);
static_assert(StreamWrapperConcept<OutputStreamWrapper<std::ostream>>);
} // namespace ipdf::stream

#endif // __IPDF_STREAM_IO_STREAM_HH

// EOF
