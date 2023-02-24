// GTest Entry of STL I/O stream operations
// Copyright(c) Stephen Zhang 2023. All Right Reserved.

// NOTE: wchar_t and related streams will be added in the future

#include "IoStream.hh"
#include "TestStreamUtils.hh"

#include <gtest/gtest.h>
#include <limits>
#include <sstream>

namespace ipdf::test
{
// NOTE: use stringstream as the tested object
class InputStreamTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        generateContents(rawContents_, rawContents_ + generatedSize_, 1, std::numeric_limits<char>::max());
        iss_ = std::istringstream(rawContents_);
    }

    void TearDown() override {}

    static constexpr size_t generatedSize_ { 1024 };

    char               rawContents_[generatedSize_] { 0 };
    std::istringstream iss_;
};

TEST_F(InputStreamTest, TakeAndTell)
{
    static constexpr size_t pBufferSize { 12 };

    char pBuffer[pBufferSize] {};
    auto ssw = stream::InputStream<std::istringstream>(iss_, pBuffer, pBufferSize);

    for (size_t i = 0; i < generatedSize_; i++)
    {
        EXPECT_EQ(rawContents_[i], ssw.take());
        EXPECT_EQ(i + 1, ssw.tell());
    }
}

TEST_F(InputStreamTest, Peek)
{
    static constexpr size_t pBufferSize { 64 };

    char pBuffer[pBufferSize] { 0 };
    auto ssw = stream::InputStream(iss_, pBuffer, pBufferSize);

    EXPECT_EQ(rawContents_[0], ssw.take());
}

TEST_F(InputStreamTest, Peek4)
{
    static constexpr size_t pBufferSize { 512 };

    char        pBuffer[pBufferSize] { 0 };
    auto        ssw     = ipdf::stream::InputStream(iss_, pBuffer, pBufferSize);
    const auto* current = ssw.peek4();

    for (size_t i = 0; i < 4; i++) EXPECT_EQ(current[i], rawContents_[i]);
}
} // namespace ipdf::test
