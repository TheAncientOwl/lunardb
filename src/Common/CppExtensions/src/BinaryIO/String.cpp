#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO {

namespace Serializer::Internal {

template <>
void serialize(std::ostream& os, std::string const& obj)
{
    serialize(os, obj.length());
    os.write(obj.c_str(), sizeof(std::string::value_type) * obj.length());
}

} // namespace Serializer::Internal

namespace Deserializer::Internal {

template <>
void deserialize(std::istream& is, std::string& obj)
{
    std::string::size_type length{0};
    deserialize(is, length);

    obj.resize(length);
    is.read(obj.data(), sizeof(std::string::value_type) * obj.length());
}

} // namespace Deserializer::Internal

} // namespace LunarDB::Common::CppExtensions::BinaryIO
