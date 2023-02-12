// File R/W operations with stream-like styles
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_FILE_STREAM_HH
#define __IPDF_STREAM_FILE_STREAM_HH

#include "Concepts.hh"

#include <cstdio>

namespace ipdf::stream
{
class FileReadStream : public BasicInputStreamWrapper<FileReadStream>
{
public:
    FileReadStream()  = delete;
    ~FileReadStream() = default;

    FileReadStream(std::FILE* fp, Ch* buffer, size_t bufferSize);

    // not implemented
    void put(Ch) { IPDF_ASSERT(false); }
    void puts(Ch, size_t) { IPDF_ASSERT(false); }
    bool flush() { IPDF_ASSERT(false); }

private:
    void read() override;

    std::FILE* fp_;
};

class FileWriteStream : public BasicOutputStreamWrapper<FileWriteStream>
{
public:
    FileWriteStream(std::FILE* fp, Ch* buffer, size_t bufferSize);
    ~FileWriteStream()                      = default;

    bool flush() override;

    // not implemented
    [[noreturn]] Ch        take() { IPDF_ASSERT(false); }
    [[noreturn]] Ch        peek() { IPDF_ASSERT(false); }
    [[noreturn]] const Ch* peek4() { IPDF_ASSERT(false); }
    [[noreturn]] size_t    tell() { IPDF_ASSERT(false); }

private:
    std::FILE* fp_;
};
} // namespace ipdf::stream

#endif // __IPDF_STREAM_FILE_STREAM_HH

// EOF
