// I/O stream wrapper for STL streams:
//      - istream, ifstream, wistream, wifstream
//      - ostream, ofstream, wostream, wofstream
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#pragma once

#include "Wrapper.hh"

namespace ipdf::stream
{
template <RawInputStream StreamT = std::istream>
class InputStream : public BasicInputStreamWrapper<StreamT>
{
public:
    using StreamType = typename BasicInputStreamWrapper<StreamT>::StreamType;
    using Ch         = typename BasicInputStreamWrapper<StreamT>::Ch;

    InputStream(StreamType is, Ch* buffer, size_t bufferSize)
        : BasicInputStreamWrapper<StreamT>(is, buffer, bufferSize)
    {
        // NOTE: https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-types
        this->read();
    }

    ~InputStream() = default;

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

template <RawOutputStream StreamT = std::ostream>
class OutputStream : public BasicOutputStreamWrapper<StreamT>
{
public:
    using StreamType = typename BasicOutputStreamWrapper<StreamT>::StreamType;
    using Ch         = typename BasicOutputStreamWrapper<StreamT>::Ch;

    OutputStream(StreamType os)
        : BasicOutputStreamWrapper<StreamT>(os, nullptr, 0)
    {
    }

    ~OutputStream() = default;

    void put(Ch c) override { this->stream_.put(c); }
    void write(Ch* src, size_t n) override { this->stream_.write(src, n); }

    void puts(Ch c, size_t n) override
    {
        for (size_t i = 0; i < n; i++) put(c);
    }

    bool flush() override
    {
        this->stream_.flush();
        return true;
    }
};
} // namespace ipdf::stream

// EOF
