#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO {

namespace Serializer::Internal {

template <>
void serialize(std::ostream& os, std::string_view const& obj)
{
    serialize(os, obj.length());
    os.write(obj.data(), sizeof(std::string_view::value_type) * obj.length());
}

} // namespace Serializer::Internal

namespace Deserializer::Internal {

template <>
void deserialize(std::istream& is, std::string_view& obj)
{
    throw std::logic_error{"std::string_view's cannot be deserialized..."};
}

} // namespace Deserializer::Internal

} // namespace LunarDB::Common::CppExtensions::BinaryIO
