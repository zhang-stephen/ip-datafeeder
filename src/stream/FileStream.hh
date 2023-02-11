// File R/W operations with stream-like styles
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_FILE_STREAM_HH
#define __IPDF_STREAM_FILE_STREAM_HH

#include "Concepts.hh"
#include "Tools.hh"

#include <cstdio>

namespace ipdf::stream
{
class FileReadStream
{
public:
    using Ch = char;

    FileReadStream()  = delete;
    ~FileReadStream() = default;

    FileReadStream(std::FILE* fp, Ch* buffer, size_t bufferSize)
        : fp_(fp)
        , buffer_(buffer)
        , bufferLast_(nullptr)
        , current_(buffer_)
        , bufferSize_(bufferSize)
        , count_(0)
        , readCount_(0)
        , eof_(false)
    {
        IPDF_ASSERT(fp_ != nullptr);
        IPDF_ASSERT(bufferSize_ >= 4);
        read();
    }

    Ch        peek() { return *current_; }
    const Ch* peek4() { return (current_ + 4 - !eof_ <= bufferLast_) ? current_ : nullptr; }
    size_t    tell() { return count_ + static_cast<size_t>(current_ - buffer_); }

    Ch take()
    {
        Ch c = *current_;
        read();
        return c;
    }

    // not implemented
    void put(Ch) { IPDF_ASSERT(false); }
    void flush() { IPDF_ASSERT(false); }

private:
    void read()
    {
        if (current_ < bufferLast_)
        {
            current_++;
        }
        else if (!eof_)
        {
            count_      += readCount_;
            readCount_  = std::fread(buffer_, sizeof(Ch), bufferSize_, fp_);
            bufferLast_ = buffer_ + readCount_ - 1;
            current_    = buffer_;

            if (readCount_ < bufferSize_)
            {
                buffer_[readCount_] = '\0';
                bufferLast_++;
                eof_ = true;
            }
        }
    }

    std::FILE* fp_;
    Ch*        buffer_;
    Ch*        bufferLast_;
    Ch*        current_;
    size_t     bufferSize_;
    size_t     count_;
    size_t     readCount_;
    bool       eof_;
};

class FileWriteStream
{
public:
    using Ch = char;

    FileWriteStream()                       = delete;
    FileWriteStream(const FileWriteStream&) = delete;
    FileWriteStream(FileWriteStream&&)      = delete;
    ~FileWriteStream()                      = default;

    FileWriteStream(std::FILE* fp, Ch* buffer, size_t bufferSize) {}

    // not implemented
    inline Ch peek()
    {
        IPDF_ASSERT(false);
        return 0;
    }
    Ch peek4()
    {
        IPDF_ASSERT(false);
        return 0;
    }
    size_t tell()
    {
        IPDF_ASSERT(false);
        return 0;
    }

private:
    std::FILE* fp_;
    Ch*        buffer_;
    Ch*        bufferLast_;
    Ch*        current_;
};
} // namespace ipdf::stream

#endif // __IPDF_STREAM_FILE_STREAM_HH

// EOF
