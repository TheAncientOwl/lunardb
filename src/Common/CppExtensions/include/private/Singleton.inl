#include "LunarDB/Common/CppExtensions/Singleton.hpp"

namespace LunarDB::CppExtensions::DesignPatterns {

template <typename ObjectType>
ObjectType& Singleton<ObjectType>::Instance()
{
    static ObjectType s_instance{};
    return s_instance;
}

} // namespace LunarDB::CppExtensions::DesignPatterns
