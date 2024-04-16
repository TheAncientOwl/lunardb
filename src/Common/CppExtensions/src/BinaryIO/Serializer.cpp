#include "Common/CppExtensions/BinaryIO.hpp"

#define PROVIDE_POD_SERIALIZER_FOR(type) \
template<> \
void serializeImpl(std::ostream& os, const type& obj) \
{ \
    os.write(reinterpret_cast<const char*>(&obj), sizeof(type)); \
} \

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

PROVIDE_POD_SERIALIZER_FOR(std::int8_t)
PROVIDE_POD_SERIALIZER_FOR(std::int16_t)
PROVIDE_POD_SERIALIZER_FOR(std::int32_t)
PROVIDE_POD_SERIALIZER_FOR(std::int64_t)
PROVIDE_POD_SERIALIZER_FOR(std::uint8_t)
PROVIDE_POD_SERIALIZER_FOR(std::uint16_t)
PROVIDE_POD_SERIALIZER_FOR(std::uint32_t)
PROVIDE_POD_SERIALIZER_FOR(std::uint64_t)

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer
