#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer::Implementation {

template <>
void deserialize(std::istream& is, std::string& obj)
{
    std::string::size_type length{0};
    deserialize(is, length);

    obj.resize(length);
    is.read(obj.data(), sizeof(std::string::value_type) * obj.length());
}

template <>
void deserialize(std::istream& is, std::string_view& obj)
{
    throw std::logic_error{"string_view's cannot be deserialized..."};
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer::Implementation
