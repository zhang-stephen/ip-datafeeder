// File R/W operations with stream-like styles
// Copyright (c) Stephen Zhang 2023. All Right Reserved.

#ifndef __IPDF_STREAM_FILE_STREAM_HH
#define __IPDF_STREAM_FILE_STREAM_HH

#include "Concepts.hh"

#include <cstdio>

namespace ipdf::stream
{
class FileReadStream : public BasicInputStreamWrapper<std::FILE*>
{
public:
    FileReadStream()  = delete;
    ~FileReadStream() = default;

    FileReadStream(std::FILE* fp, Ch* buffer, size_t bufferSize);

private:
    void read() override;

    std::FILE* fp_;
};

class FileWriteStream : public BasicOutputStreamWrapper<std::FILE*>
{
public:
    FileWriteStream(std::FILE* fp, Ch* buffer, size_t bufferSize);
    ~FileWriteStream() = default;

    bool flush() override;
    void put(Ch c) override;
    void puts(Ch c, size_t n) override;

private:
    std::FILE* fp_;
};
} // namespace ipdf::stream

#endif // __IPDF_STREAM_FILE_STREAM_HH

// EOF
