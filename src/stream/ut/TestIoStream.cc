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
        rawContents_.reserve(generatedSize_);
        generateContents(rawContents_.begin(), rawContents_.end(), 1, std::numeric_limits<char>::max());
        iss_ = std::istringstream(rawContents_);
    }

    void TearDown() override {}

    static constexpr size_t generatedSize_ { 1024 };
    std::string             rawContents_ {};
    std::istringstream      iss_;
};

TEST_F(InputStreamTest, TakeAndTell)
{
    static constexpr size_t pBufferSize { 12 };

    char pBuffer[pBufferSize] {};
    auto ssw = stream::InputStream<std::istringstream>(iss_, pBuffer, pBufferSize);

    for (size_t i = 0; i < generatedSize_; i++)
    {
        EXPECT_EQ(rawContents_[i], ssw.take());
        EXPECT_EQ(i, ssw.tell());
    }
}

} // namespace ipdf::test
