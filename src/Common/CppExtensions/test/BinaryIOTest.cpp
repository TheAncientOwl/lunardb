#include <gtest/gtest.h>
#include <fstream>

#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Tests {

using namespace Serializer;
using namespace Deserializer;

#define AS_STRING_(x) #x
#define AS_STRING(x) AS_STRING_(x)
#define TEMP_FILE "/tmp/lunardb_binary_test." AS_STRING(__LINE__) ".tmp"

TEST(Common_CppExtensions_BinaryIOTest, std_uint8_t)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const std::uint8_t out_value{ 2 };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    std::uint8_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint16_t)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const std::uint16_t out_value{ 221 };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    std::uint16_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint32_t)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const std::uint32_t out_value{ 2312312 };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    std::uint32_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint64_t)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const std::uint64_t out_value{ 42312312 };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    std::uint64_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int8_t)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const std::int8_t out_value{ -2 };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    std::int8_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int16_t)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const std::int16_t out_value{ -221 };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    std::int16_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int32_t)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const std::int32_t out_value{ -2312312 };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    std::int32_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int64_t)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const std::int64_t out_value{ -42312312 };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    std::int64_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, char)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const char out_value{ 'c' };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    char in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, bool)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const bool out_value{ true };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    bool in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, float)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const float out_value{ true };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    float in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, double)
{
    static constexpr auto c_temp_file{ TEMP_FILE };

    std::ofstream out{ c_temp_file, std::ios::binary };
    const double out_value{ true };
    serialize(out, out_value);
    out.close();

    std::ifstream in{ c_temp_file, std::ios::binary };
    double in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Tests
