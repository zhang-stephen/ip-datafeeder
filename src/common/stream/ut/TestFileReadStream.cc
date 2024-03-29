// GTest Entry of File I/O operations
// Copyright(c) Stephen Zhang 2023. All Right Reserved.

#include "Config.hh"
#include "FileStream.hh"
#include "Logger.hh"
#include "Platform.hh"
#include "TestStreamUtils.hh"

#include <algorithm>
#include <array>
#include <filesystem>
#include <gtest/gtest.h>
#include <limits>
#include <random>
#include <string>

namespace ipdf::test
{
namespace fs = std::filesystem;

class FileReadStreamTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        fs::path generatedFileDir = CMAKE_BINARY_DIR;
        fs::path generatedFile    = generatedFileDir / "src/stream/TestFileReadStream.bin";

        if (!fs::exists(generatedFile))
        {
            generateContents(rawContents_.begin(), rawContents_.end(), 0, std::numeric_limits<char>::max());
            ASSERT_TRUE(createRandomFile(generatedFile));
            fp_ = std::fopen(generatedFile.string().c_str(), readFlags().c_str());
            ASSERT_NE(fp_, nullptr);
        }
        else
        {
            fp_ = std::fopen(generatedFile.string().c_str(), readFlags().c_str());
            ASSERT_NE(fp_, nullptr);
            std::fread(rawContents_.data(), sizeof(char), generatedFileSize_, fp_);
            resetFp();
        }
    }

    void TearDown() override { std::fclose(fp_); }

    static constexpr size_t              generatedFileSize_ { 1024U };
    std::array<char, generatedFileSize_> rawContents_ {};
    std::FILE*                           fp_ { nullptr };

private:
    bool createRandomFile(const fs::path& p)
    {
        if (p.empty()) return false;

        auto* tmpFp = std::fopen(p.string().c_str(), writeFlags().c_str());

        if (tmpFp == nullptr)
        {
            IPDF_LOG_WRN("open test file failed: {}", std::strerror(errno));
            return false;
        }

        auto writtenCnt = fwrite(rawContents_.data(), sizeof(char), generatedFileSize_, tmpFp);

        if (writtenCnt != generatedFileSize_)
        {
            IPDF_LOG_WRN("Create example file failed! Expected bytes: {}, against written into file: {}",
                         generatedFileSize_,
                         writtenCnt);
            return false;
        }

        std::fclose(tmpFp);
        return true;
    }

    void resetFp() const
    {
        if (std::fseek(fp_, 0, 0) != 0)
        {
            IPDF_LOG_WRN("Reset the file pointer failed!");
        }
    }

    static constexpr std::string writeFlags() { return utility::isWin32() ? "wb" : "w"; }
    static constexpr std::string readFlags() { return utility::isWin32() ? "rb" : "r"; }
};

TEST_F(FileReadStreamTest, TakeAndTell)
{
    char buffer[4] { 0 };
    auto fws = stream::FileReadStream(fp_, buffer, 4);

    for (size_t i = 0; i < generatedFileSize_; i++)
    {
        IPDF_LOG_TRC("Index = {}, Cached = {}", i, uint8_t(buffer[i % 4]));
        EXPECT_EQ(fws.take(), rawContents_.at(i));
        EXPECT_EQ(fws.tell(), i + 1);
    }
}

TEST_F(FileReadStreamTest, Peek)
{
    static constexpr size_t bufferSize = 12;

    char buffer[bufferSize] { 0 };
    auto fws = stream::FileReadStream(fp_, buffer, bufferSize);

    EXPECT_EQ(fws.peek(), rawContents_[0]);
}

TEST_F(FileReadStreamTest, Peek4)
{
    static constexpr size_t bufferSize { 128 };

    char        buffer[bufferSize] { 0 };
    auto        fws     = stream::FileReadStream(fp_, buffer, bufferSize);
    const auto* current = fws.peek4();

    for (size_t i = 0; i < 4; i++)
    {
        EXPECT_EQ(current[i], rawContents_.at(i));
    }
}
} // namespace ipdf::test
