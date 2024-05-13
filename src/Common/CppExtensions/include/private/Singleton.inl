#include "LunarDB/Common/CppExtensions/Singleton.hpp"

namespace LunarDB::Common::CppExtensions::DesignPatterns {

template <typename EntityType>
EntityType& Singleton<EntityType>::Instance()
{
    static EntityType s_instance{};
    return s_instance;
}

} // namespace LunarDB::Common::CppExtensions::DesignPatterns
