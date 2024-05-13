#pragma once

namespace LunarDB::CppExtensions::DesignPatterns {

template <typename ObjectType>
class Singleton
{
public:
    static ObjectType& Instance();

private:
    Singleton() = default;

public:
    ~Singleton() = default;
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;
    Singleton(Singleton&&) noexcept = delete;
    Singleton& operator=(Singleton&&) noexcept = delete;
};

} // namespace LunarDB::CppExtensions::DesignPatterns

#include "LunarDB/Common/CppExtensions/private/Singleton.inl"