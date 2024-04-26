#include <fstream>
#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <filesystem>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Common/CppExtensions/BinaryIO.hpp"
#include "Common/CppExtensions/testing/TempFileSystemGuards.hpp"

#define AS_STRING_(x) #x
#define AS_STRING(x) AS_STRING_(x)
#define TEMP_FILE "/tmp/lunardb_binary_test." AS_STRING(__LINE__) ".tmp"

namespace std {

template <typename T>
bool operator==(std::span<T> const& lhs, std::vector<T> const& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }

    for (auto index = 0; index < lhs.size(); ++index)
    {
        if (lhs[index] != rhs[index])
        {
            return false;
        }
    }

    return true;
}

template <typename T, std::size_t Size>
bool operator==(std::span<T> const& lhs, std::array<T, Size> const& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }

    for (auto index = 0; index < lhs.size(); ++index)
    {
        if (lhs[index] != rhs[index])
        {
            return false;
        }
    }

    return true;
}

} // namespace std

namespace LunarDB::Common::CppExtensions::BinaryIO::Tests {

using namespace Serializer;
using namespace Deserializer;

using TempFileGuard = Testing::TempFileSystemGuards::TempFileGuard;

TEST(Common_CppExtensions_BinaryIOTest, std_uint8_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::uint8_t const out_value{2};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::uint8_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint16_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::uint16_t const out_value{221};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::uint16_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint32_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::uint32_t const out_value{2312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::uint32_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_uint64_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::uint64_t const out_value{42312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::uint64_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int8_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::int8_t const out_value{-2};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::int8_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int16_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::int16_t const out_value{-221};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::int16_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int32_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::int32_t const out_value{-2312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::int32_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_int64_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::int64_t const out_value{-42312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::int64_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_size_t)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::size_t const out_value{42312312};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::size_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, char)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    const char out_value{'c'};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    char in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, bool)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    bool const out_value{true};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    bool in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, float)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    float const out_value{true};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    float in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, double)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    double const out_value{true};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    double in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_string)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::string const out_value{"some string no idea    \t\t\n "};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::string in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_string_view)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::string_view const out_value{"some string_view no idea    \t\t\n "};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::string in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_vector)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::vector<float> const out_value{2.2f, 3.4f};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::vector<float> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_tuple)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

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

    EXPECT_EQ(out_value, in_value);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& values)
{
    std::for_each(
        std::begin(values), std::end(values), [&os](auto const& value) { os << value << ", "; });
    return os;
}

std::ostream& operator<<(std::ostream& os, std::string const& str)
{
    os << "\"" << str << "\"";
    return os;
}

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

    bool operator==(Object const& rhs) const { return makeTuple() == rhs.makeTuple(); }

    friend std::ostream& operator<<(std::ostream& os, Object const& rhs)
    {
        os << "Object{ a: " << rhs.a << "| b: " << rhs.b << "| c: " << rhs.c << "| d: " << rhs.d
           << "| e: " << rhs.e << "| f: " << rhs.f << "| g: " << rhs.g << "| h: " << rhs.h << " }";
        return os;
    }
};

TEST(Common_CppExtensions_BinaryIOTest, object)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

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

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_pair)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::pair<std::string, int> const out_value{"some string no idea    \t\t\n ", 22};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::pair<std::string, int> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, enum)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

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

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_map)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::map<std::string, double> const out_value{
        {"2.2", 2.2}, {"555.555", 555.555}, {"123456.7890", 123456.7890}};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::map<std::string, double> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_multimap)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::multimap<std::string, double> const out_value{
        {"2.2", 2.2}, {"555.555", 555.555}, {"123456.7890", 123456.7890}, {"2.2", 2.2}};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::multimap<std::string, double> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_unordered_map)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::unordered_map<std::string, double> const out_value{
        {"2.2", 2.2}, {"555.555", 555.555}, {"123456.7890", 123456.7890}};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::unordered_map<std::string, double> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_unordered_multimap)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::unordered_multimap<std::string, double> const out_value{
        {"2.2", 2.2}, {"555.555", 555.555}, {"123456.7890", 123456.7890}, {"2.2", 2.2}};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::unordered_multimap<std::string, double> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_set)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::set<std::string> const out_value{"str1", "str2", "str3", "str4"};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::set<std::string> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_multiset)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::multiset<std::string> const out_value{"str1", "str2", "str3", "str2"};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::multiset<std::string> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_unordered_set)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::unordered_set<std::string> const out_value{"str1", "str2", "str3"};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::unordered_set<std::string> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_unordered_multiset)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::unordered_multiset<std::string> const out_value{"str1", "str2", "str3", "str2"};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::unordered_multiset<std::string> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_array)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    using array_t = std::array<std::string, 4>;

    std::ofstream out{c_temp_file, std::ios::binary};
    array_t const out_value{"str1", "str2", "str3", "str2"};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    array_t in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_list)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::list<float> const out_value{2.2f, 3.4f};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::list<float> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_forward_list)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::forward_list<float> const out_value{2.2f, 3.4f};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::forward_list<float> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_deque)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::deque<float> const out_value{2.2f, 3.4f};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::deque<float> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_span_vector)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::vector<float> values{2.2f, 3.4f};
    std::span<float> const out_value{values};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::vector<float> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_span_array)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::array<float, 2> values{2.2f, 3.4f};
    std::span<float> const out_value{values};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::array<float, 2> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_span_carray)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    float values[] = {2.2f, 3.4f};
    std::span<float> const out_value{values};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::array<float, 2> in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

TEST(Common_CppExtensions_BinaryIOTest, std_filesystem_path)
{
    static TempFileGuard c_temp_file{TEMP_FILE};

    std::ofstream out{c_temp_file, std::ios::binary};
    std::filesystem::path const out_value{std::filesystem::current_path()};
    serialize(out, out_value);
    out.close();

    std::ifstream in{c_temp_file, std::ios::binary};
    std::filesystem::path in_value{};
    deserialize(in, in_value);
    in.close();

    EXPECT_EQ(out_value, in_value);
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Tests
