// File R/W operations with stream-like styles
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_FILE_STREAM_HH
#define __IPDF_STREAM_FILE_STREAM_HH

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

    FileReadStream(std::FILE* fp, Ch* buffer, size_t bufferSize);

    Ch        peek();
    const Ch* peek4();
    size_t    tell();
    Ch        take();

    // not implemented
    void put(Ch) { IPDF_ASSERT(false); }
    void put(Ch, size_t) { IPDF_ASSERT(false); }
    void flush() { IPDF_ASSERT(false); }

private:
    void read();

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

    FileWriteStream(std::FILE* fp, Ch* buffer, size_t bufferSize);

    void put(Ch c);
    void put(Ch c, size_t n);
    void flush();

    // not implemented
    [[noreturn]] Ch        take() { IPDF_ASSERT(false); }
    [[noreturn]] Ch        peek() { IPDF_ASSERT(false); }
    [[noreturn]] const Ch* peek4() { IPDF_ASSERT(false); }
    [[noreturn]] size_t    tell() { IPDF_ASSERT(false); }

private:
    std::FILE* fp_;
    Ch*        buffer_;
    Ch*        bufferEnd_;
    Ch*        current_;
};
} // namespace ipdf::stream

#endif // __IPDF_STREAM_FILE_STREAM_HH

// EOF
