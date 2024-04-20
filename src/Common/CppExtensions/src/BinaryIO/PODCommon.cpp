#include "Common/CppExtensions/BinaryIO.hpp"

#define PROVIDE_POD_SERIALIZER_FOR(type)                             \
    namespace Serializer::Internal {                                 \
    template <>                                                      \
    void serialize(std::ostream& os, type const& obj)                \
    {                                                                \
        os.write(reinterpret_cast<const char*>(&obj), sizeof(type)); \
    }                                                                \
    } // namespace Serializer::Internal

#define PROVIDE_POD_DESERIALIZER_FOR(type)                    \
    namespace Deserializer::Internal {                        \
    template <>                                               \
    void deserialize(std::istream& is, type& obj)             \
    {                                                         \
        is.read(reinterpret_cast<char*>(&obj), sizeof(type)); \
    }                                                         \
    } // namespace Deserializer::Internal

#define PROVIDE_POD_SERIALIZER_DESERIALIZER(type) \
    PROVIDE_POD_SERIALIZER_FOR(type)              \
    PROVIDE_POD_DESERIALIZER_FOR(type)

namespace LunarDB::Common::CppExtensions::BinaryIO {

PROVIDE_IMPL_FOR_PODS(PROVIDE_POD_SERIALIZER_DESERIALIZER);

} // namespace LunarDB::Common::CppExtensions::BinaryIO
