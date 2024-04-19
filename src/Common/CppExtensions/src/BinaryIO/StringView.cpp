#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO {

namespace Serializer::Implementation {

template <>
void serialize(std::ostream& os, std::string_view const& obj)
{
    serialize(os, obj.length());
    os.write(obj.data(), sizeof(std::string_view::value_type) * obj.length());
}

} // namespace Serializer::Implementation

namespace Deserializer::Implementation {

template <>
void deserialize(std::istream& is, std::string_view& obj)
{
    throw std::logic_error{"std::string_view's cannot be deserialized..."};
}

} // namespace Deserializer::Implementation

} // namespace LunarDB::Common::CppExtensions::BinaryIO
