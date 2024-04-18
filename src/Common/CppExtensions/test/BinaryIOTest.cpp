#include <fstream>
#include <gtest/gtest.h>

#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Tests {

using namespace Serializer;
using namespace Deserializer;

#define AS_STRING_(x) #x
#define AS_STRING(x) AS_STRING_(x)
#define TEMP_FILE "/tmp/lunardb_binary_test." AS_STRING(__LINE__) ".tmp"

TEST(Common_CppExtensions_BinaryIOTest, std_uint8_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::uint8_t const out_value{2};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::uint8_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint16_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::uint16_t const out_value{221};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::uint16_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint32_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::uint32_t const out_value{2312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::uint32_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint64_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::uint64_t const out_value{42312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::uint64_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int8_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::int8_t const out_value{-2};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::int8_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int16_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::int16_t const out_value{-221};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::int16_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int32_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::int32_t const out_value{-2312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::int32_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int64_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::int64_t const out_value{-42312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::int64_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_size_t)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::size_t const out_value{42312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::size_t in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, char)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    const char out_value{'c'};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    char const in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, bool)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    bool const out_value{true};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    bool in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, float)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    float const out_value{true};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    float in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, double)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    double const out_value{true};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    double in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_string)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::string const out_value{"some string no idea    \t\t\n "};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::string in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_string_view)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::string_view const out_value{"some string_view no idea    \t\t\n "};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::string_view in_value_sv{};
    EXPECT_THROW({ deserialize(in, in_value_sv); }, std::logic_error);

    std::string in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Tests
