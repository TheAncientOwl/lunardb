#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO {

namespace Serializer::Implementation {

template <>
void serialize(std::ostream& os, std::string const& obj)
{
    serialize(os, obj.length());
    os.write(obj.c_str(), sizeof(std::string::value_type) * obj.length());
}

} // namespace Serializer::Implementation

namespace Deserializer::Implementation {

template <>
void deserialize(std::istream& is, std::string& obj)
{
    std::string::size_type length{0};
    deserialize(is, length);

    obj.resize(length);
    is.read(obj.data(), sizeof(std::string::value_type) * obj.length());
}

} // namespace Deserializer::Implementation

} // namespace LunarDB::Common::CppExtensions::BinaryIO
