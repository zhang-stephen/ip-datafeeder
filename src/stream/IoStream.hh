// I/O stream wrapper for STL streams:
//      - istream, ifstream, wistream, wifstream
//      - ostream, ofstream, wostream, wofstream
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_IO_STREAM_HH
#define __IPDF_STREAM_IO_STREAM_HH

#include "Wrapper.hh"

namespace ipdf::stream
{
template <RawInputStream _StreamT = std::istream>
class InputStream : public BasicInputStreamWrapper<_StreamT>
{
public:
    using StreamType = typename BasicInputStreamWrapper<_StreamT>::StreamType;
    using Ch         = typename BasicInputStreamWrapper<_StreamT>::Ch;

    InputStream(StreamType is, Ch* buffer, size_t bufferSize)
        : BasicInputStreamWrapper<_StreamT>(is, buffer, bufferSize)
    {
        // NOTE: https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-types
        this->read();
    }

protected:
    void read() override
    {
        if (this->current_ < this->bufferLast_)
        {
            this->current_++;
        }
        else if (!this->eof_)
        {
            this->count_      += this->readCount_;
            this->readCount_  = this->bufferSize_;
            this->bufferLast_ = this->buffer_ + this->readCount_ - 1;
            this->current_    = this->buffer_;

            if (!this->stream_.read(this->buffer_, this->bufferSize_))
            {
                this->readCount_     = this->stream_.gcount();
                this->bufferLast_    = this->buffer_ + this->readCount_;
                *(this->bufferLast_) = '\0';
                this->eof_           = true;
            }
        }
    }
};

template <RawOutputStream _StreamT = std::ostream>
class OutputStream : public BasicOutputStreamWrapper<_StreamT>
{
public:
    using StreamType = typename BasicOutputStreamWrapper<_StreamT>::StreamType;
    using Ch         = typename BasicOutputStreamWrapper<_StreamT>::Ch;

    OutputStream(StreamType os)
        : BasicOutputStreamWrapper<_StreamT>(os, nullptr, 0)
    {
    }

    bool flush() override
    {
        this->stream_.flush();
        return true;
    }

    void put(Ch c) override { this->stream_.put(c); }

    void puts(Ch c, size_t n) override
    {
        for (size_t i = 0; i < n; i++) put(c);
    }
};
} // namespace ipdf::stream

#endif // __IPDF_STREAM_IO_STREAM_HH

// EOF
