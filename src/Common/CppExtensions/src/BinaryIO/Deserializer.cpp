#include "Common/CppExtensions/BinaryIO.hpp"

#define PROVIDE_POD_DESERIALIZER_FOR(type) \
template<> \
void deserializeImpl(std::istream& is, type& obj) \
{ \
    is.read(reinterpret_cast<char*>(&obj), sizeof(type)); \
}

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer {

PROVIDE_POD_DESERIALIZER_FOR(std::int8_t)
PROVIDE_POD_DESERIALIZER_FOR(std::int16_t)
PROVIDE_POD_DESERIALIZER_FOR(std::int32_t)
PROVIDE_POD_DESERIALIZER_FOR(std::int64_t)
PROVIDE_POD_DESERIALIZER_FOR(std::uint8_t)
PROVIDE_POD_DESERIALIZER_FOR(std::uint16_t)
PROVIDE_POD_DESERIALIZER_FOR(std::uint32_t)
PROVIDE_POD_DESERIALIZER_FOR(std::uint64_t)

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer
