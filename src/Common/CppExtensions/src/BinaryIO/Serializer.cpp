#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

template <>
void serializeImpl(std::ostream& os, const std::string& obj)
{
    serialize(os, obj.length());
    os.write(obj.c_str(), sizeof(std::string::value_type) * obj.length());
}

template <>
void serializeImpl(std::ostream& os, const std::string_view& obj)
{
    serialize(os, obj.length());
    os.write(obj.data(), sizeof(std::string_view::value_type) * obj.length());
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer
