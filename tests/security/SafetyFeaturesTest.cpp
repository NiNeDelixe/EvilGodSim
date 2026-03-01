#include <gtest/gtest.h>

#include "enginecore/core/EnginePaths.h"
#include "enginecore/utils/StringUtils.h"

TEST(SafetyFeatures, ListDirectoryWithNoRootsReturnsEmpty)
{
    EnginePaths paths;

    EXPECT_NO_THROW({
        auto entries = paths.listDirectory("mods");
        EXPECT_TRUE(entries.empty());
    });
}

TEST(SafetyFeatures, Utf8LenRejectsInvalidLeadingByte)
{
    EXPECT_THROW(UTILS_NAMESPACE::string::utf8_len(static_cast<ubyte_t>(0x80)), std::runtime_error);
}

TEST(SafetyFeatures, DecodeUtf8ParsesTwoByteCodepoint)
{
    const char* encoded = "\xC2\xA9"; // U+00A9
    uint_t size = 0;

    const uint32_t codepoint = UTILS_NAMESPACE::string::decode_utf8(size, encoded);

    EXPECT_EQ(size, 2u);
    EXPECT_EQ(codepoint, 0xA9u);
}
