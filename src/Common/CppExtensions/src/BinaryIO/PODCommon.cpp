#include "Common/CppExtensions/BinaryIO.hpp"

#define PROVIDE_POD_SERIALIZER_FOR(type)                             \
    namespace Serializer::Implementation {                           \
    template <>                                                      \
    void serialize(std::ostream& os, type const& obj)                \
    {                                                                \
        os.write(reinterpret_cast<const char*>(&obj), sizeof(type)); \
    }                                                                \
    } // namespace Serializer::Implementation

#define PROVIDE_POD_DESERIALIZER_FOR(type)                    \
    namespace Deserializer::Implementation {                  \
    template <>                                               \
    void deserialize(std::istream& is, type& obj)             \
    {                                                         \
        is.read(reinterpret_cast<char*>(&obj), sizeof(type)); \
    }                                                         \
    } // namespace Deserializer::Implementation

#define PROVIDE_POD_SERIELIZER_DESERIALIZER(type) \
    PROVIDE_POD_SERIALIZER_FOR(type)              \
    PROVIDE_POD_DESERIALIZER_FOR(type)

namespace LunarDB::Common::CppExtensions::BinaryIO {

PROVIDE_IMPL_FOR_PODS(PROVIDE_POD_SERIELIZER_DESERIALIZER);

} // namespace LunarDB::Common::CppExtensions::BinaryIO
