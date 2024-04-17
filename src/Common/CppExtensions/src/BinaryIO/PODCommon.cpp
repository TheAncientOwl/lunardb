#include "Common/CppExtensions/BinaryIO.hpp"

#define PROVIDE_POD_SERIALIZER_FOR(type) \
namespace Serializer { \
template<> \
void serializeImpl(std::ostream& os, const type& obj) \
{ \
    os.write(reinterpret_cast<const char*>(&obj), sizeof(type)); \
} \
} // namespace Serializer

#define PROVIDE_POD_DESERIALIZER_FOR(type) \
namespace Deserializer { \
template<> \
void deserializeImpl(std::istream& is, type& obj) \
{ \
    is.read(reinterpret_cast<char*>(&obj), sizeof(type)); \
} \
}

#define PROVIDE_POD_SERIELIZER_DESERIALIZER(type) \
PROVIDE_POD_SERIALIZER_FOR(type) \
PROVIDE_POD_DESERIALIZER_FOR(type)

namespace LunarDB::Common::CppExtensions::BinaryIO {

PROVIDE_IMPL_FOR_PODS(PROVIDE_POD_SERIELIZER_DESERIALIZER);

} // namespace LunarDB::Common::CppExtensions::BinaryIO
