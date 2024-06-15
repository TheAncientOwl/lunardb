#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO {

namespace Serializer {

template <>
void serialize(std::ostream& os, std::string_view const& sv)
{
    serialize(os, sv.length());
    os.write(sv.data(), sizeof(std::string::value_type) * sv.length());
}

template <>
void serialize(std::ostream& os, std::string const& str)
{
    serialize(os, str.length());
    os.write(str.c_str(), sizeof(std::string::value_type) * str.length());
}

template <>
void serialize(std::ostream& os, std::filesystem::path const& path)
{
    serialize(os, path.string());
}

} // namespace Serializer

namespace Deserializer {

template <>
void deserialize(std::istream& is, std::string& str)
{
    std::string::size_type length{0};
    deserialize(is, length);

    str.resize(length);
    is.read(str.data(), sizeof(std::string::value_type) * str.length());
}

template <>
void deserialize(std::istream& is, std::filesystem::path& path)
{
    std::string path_str{};
    deserialize(is, path_str);
    path.assign(std::move(path_str));
}

} // namespace Deserializer

} // namespace LunarDB::Common::CppExtensions::BinaryIO
