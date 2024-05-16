#include "LunarDB/Common/CppExtensions/Singleton.hpp"

#include <mutex>

namespace LunarDB::Common::CppExtensions::DesignPatterns {

template <typename EntityType>
EntityType& Singleton<EntityType>::Instance()
{
    static EntityType s_instance{};

    static std::once_flag s_flag{};
    std::call_once(s_flag, [] { s_instance.init(); });

    return s_instance;
}

} // namespace LunarDB::Common::CppExtensions::DesignPatterns
