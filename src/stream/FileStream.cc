// File R/W operations with stream-like styles
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#include "FileStream.hh"

#include <cstdio>

namespace ipdf::stream
{
FileReadStream::FileReadStream(std::FILE* fp, Ch* buffer, size_t bufferSize)
    : fp_(fp)
    , BasicInputStreamWrapper(buffer, bufferSize)
{
    IPDF_ASSERT(fp_ != nullptr);
    read();
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
    , BasicOutputStreamWrapper(buffer, bufferSize)
{
    IPDF_ASSERT(fp_ != nullptr);
}

bool FileWriteStream::flush()
{
    if (current_ == buffer_) return true;

    auto used   = static_cast<size_t>(current_ - buffer_);
    auto result = std::fwrite(buffer_, sizeof(Ch), used, fp_);
    current_    = buffer_;

    // NOTE: do not be treated as error if size written into file is less than buffer used.
    return result < used;
}

// concepts check
static_assert(StreamWrapperConcept<FileReadStream>);
static_assert(StreamWrapperConcept<FileWriteStream>);
} // namespace ipdf::stream

// EOF
