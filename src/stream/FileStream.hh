// File R/W operations with stream-like styles
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_FILE_STREAM_HH
#define __IPDF_STREAM_FILE_STREAM_HH

#include "IoStream.hh"

#include <algorithm>

namespace ipdf::stream
{
template <>
class InputStream<std::FILE*> : public BasicInputStreamWrapper<std::FILE*>
{
public:
    using StreamType = typename BasicInputStreamWrapper::StreamType;
    using Ch         = typename BasicInputStreamWrapper::Ch;

    InputStream(StreamType stream, Ch* buffer, size_t bufferSize)
        : BasicInputStreamWrapper(stream, buffer, bufferSize)
    {
        IPDF_ASSERT(stream_ != nullptr);
        IPDF_ASSERT(buffer_ != nullptr);
        IPDF_ASSERT(bufferSize_ >= 4); // for peek4(), used to unicode checking.
        read();
    }

    ~InputStream() = default;

protected:
    void read() override
    {
        if (current_ < bufferLast_)
        {
            current_++;
        }
        else if (!eof_)
        {
            count_      += readCount_;
            readCount_  = std::fread(buffer_, sizeof(Ch), bufferSize_, stream_);
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
};

template <>
class OutputStream<std::FILE*> : public BasicOutputStreamWrapper<std::FILE*>
{
public:
    using StreamType = BasicOutputStreamWrapper::StreamType;
    using Ch         = BasicOutputStreamWrapper::Ch;

    OutputStream(StreamType stream, Ch* buffer, size_t bufferSize)
        : BasicOutputStreamWrapper(stream, buffer, bufferSize)
    {
        IPDF_ASSERT(stream != nullptr);
        IPDF_ASSERT(buffer != nullptr);
        IPDF_ASSERT(bufferSize > 0);
    }

    ~OutputStream() = default;

    bool flush() override
    {
        if (current_ == buffer_) return true;

        auto used   = static_cast<size_t>(current_ - buffer_);
        auto result = std::fwrite(buffer_, sizeof(Ch), used, stream_);
        current_    = buffer_;

        // NOTE: do not be treated as error if size written into file is less than buffer used.
        return result <= used;
    }

    void put(Ch c) override
    {
        if (current_ >= bufferEnd_) flush();
        *current_++ = c;
    }

    void write(Ch* src, size_t n) override
    {
        if (src == nullptr) return;

        auto avail = static_cast<size_t>(bufferEnd_ - current_);

        while (n > avail)
        {
            std::copy(current_, current_ + avail, src);

            flush();
            n     -= avail;
            src   += avail;
            avail = static_cast<size_t>(bufferEnd_ - current_);
        }

        if (n > 0) std::copy(current_, current_ + n, src);
    }

    void puts(Ch c, size_t n) override
    {
        auto avail = static_cast<size_t>(bufferEnd_ - current_);

        while (n > avail)
        {
            std::fill_n(current_, avail, c);

            flush();
            n     -= avail;
            avail = static_cast<size_t>(bufferEnd_ - current_);
        }

        if (n > 0) std::fill_n(current_, n, c);
    }
};

using FileReadStream  = InputStream<std::FILE*>;
using FileWriteStream = OutputStream<std::FILE*>;
} // namespace ipdf::stream

#endif // __IPDF_STREAM_FILE_STREAM_HH

// EOF
