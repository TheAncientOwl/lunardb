#include <fstream>
#include <gtest/gtest.h>

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

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
    char in_value{};
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

TEST(Common_CppExtensions_BinaryIOTest, std_vector)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::vector<float> const out_value{2.2f, 3.4f};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::vector<float> in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_tuple)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    using type =
        std::tuple<int, bool, char, float, double, std::string, std::vector<int>, std::vector<std::string>>;

    std::ofstream out{c_temp_file, std::ios::binary};
    type const out_value{
        404,
        true,
        'x',
        2.2f,
        2.2,
        "some long string 123456789",
        std::vector<int>{1, 2, 3, 4},
        std::vector<std::string>{"somestr1", "somestr2"}};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    type in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, object)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    struct Object
    {
        int a;
        bool b;
        char c;
        float d;
        double e;
        std::string f;
        std::vector<int> g;
        std::vector<std::string> h;

        LUNAR_ENABLE_BINARY_IO(a, b, c, d, e, f, g, h);
    };

    std::ofstream out{c_temp_file, std::ios::binary};
    Object const out_value{
        404,
        true,
        'x',
        2.2f,
        2.2,
        "some long string 123456789",
        std::vector<int>{1, 2, 3, 4},
        std::vector<std::string>{"somestr1", "somestr2"}};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    Object in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value.makeTuple(), in_value.makeTuple());
}

TEST(Common_CppExtensions_BinaryIOTest, std_pair)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::pair<std::string, int> const out_value{"some string no idea    \t\t\n ", 22};
    serialize(out, out_value);
    static_assert(Common::Concepts::Pair<decltype(out_value)>);
    Serializer::Internal::serializePair(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::pair<std::string, int> in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, enum)
{
    static constexpr auto c_temp_file{TEMP_FILE};

    enum class SomeEnum : std::uint8_t
    {
        Value1 = 3,
        Value2 = 101,
        Value3 = 25
    };

    std::ofstream out{c_temp_file, std::ios::binary};
    SomeEnum const out_value{SomeEnum::Value2};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    SomeEnum in_value{};
    deserialize(in, in_value);
    in.close();

    std::remove(c_temp_file);

    EXPECT_EQ(out_value, in_value);
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Tests
