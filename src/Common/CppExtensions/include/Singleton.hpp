#pragma once

#include <mutex>

namespace LunarDB::Common::CppExtensions::DesignPatterns {

template <typename EntityType>
class Singleton
{
public:
    static EntityType& Instance();

protected:
    Singleton() = default;

    virtual void init() {};

public:
    ~Singleton() = default;
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;
    Singleton(Singleton&&) noexcept = delete;
    Singleton& operator=(Singleton&&) noexcept = delete;
};

} // namespace LunarDB::Common::CppExtensions::DesignPatterns

#define LUNAR_SINGLETON_INIT(classname)                                       \
    friend class Common::CppExtensions::DesignPatterns::Singleton<classname>; \
    void init() final override

#define LUNAR_SINGLETON_INIT_IMPL(classname) void classname::init()

#include "LunarDB/Common/CppExtensions/private/Singleton.inl"
