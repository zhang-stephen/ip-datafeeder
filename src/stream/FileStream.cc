// File R/W operations with stream-like styles
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#include "FileStream.hh"

#include "Concepts.hh"

#include <cstdio>

namespace ipdf::stream
{
FileReadStream::FileReadStream(std::FILE* fp, Ch* buffer, size_t bufferSize)
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
    IPDF_ASSERT(bufferSize_ >= 4); // for peek4(), used to unicode checking.
    read();
}

FileReadStream::Ch FileReadStream::peek()
{
    return *current_;
}

const FileReadStream::Ch* FileReadStream::peek4()
{
    return (current_ + 4 - !eof_ <= bufferLast_) ? current_ : nullptr;
}

size_t FileReadStream::tell()
{
    return count_ + static_cast<size_t>(current_ - buffer_);
}

FileReadStream::Ch FileReadStream::take()
{
    Ch c = *current_;
    read();
    return c;
}

void FileReadStream::read()
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

FileWriteStream::FileWriteStream(std::FILE* fp, Ch* buffer, size_t bufferSize)
    : fp_(fp)
    , buffer_(buffer)
    , bufferEnd_(buffer_ + bufferSize)
    , current_(buffer_)
{
    IPDF_ASSERT(fp_ != nullptr);
}

void FileWriteStream::put(Ch c)
{
    if (current_ >= bufferEnd_) flush();
    *current_++ = c;
}

void FileWriteStream::put(Ch c, size_t n)
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

void FileWriteStream::flush()
{
    if (current_ == buffer_) return;

    auto used   = static_cast<size_t>(current_ - buffer_);
    auto result = std::fwrite(buffer_, sizeof(Ch), used, fp_);
    current_    = buffer_;

    if (result < used)
    {
        // do not be treated as error if size written into file is less than buffer used.
    }
}

// concepts check
static_assert(StreamWrapper<FileReadStream>);
static_assert(StreamWrapper<FileWriteStream>);
} // namespace ipdf::stream

// EOF
