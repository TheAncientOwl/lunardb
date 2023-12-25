#pragma once

#include <memory>
#include <array>
#include <functional>

namespace LunarDB::Moonlight::Implementation {

template<typename Base, typename... Derived>
class HierarchySet
{
public:
    using BasePtr = std::shared_ptr<Base>;
    using ConstBasePtr = const BasePtr;
    using Container = std::array<BasePtr, sizeof...(Derived)>;

public:
    HierarchySet();

    BasePtr findIf(std::function<bool(Base& current)> valid);
    ConstBasePtr findIf(std::function<bool(const Base& current)> valid) const;

private:
    Container m_data;
};

template<typename Base, typename ...Derived>
inline HierarchySet<Base, Derived...>::HierarchySet()
    : m_data({ (std::make_unique<Derived>())... })
{}

template<typename Base, typename ...Derived>
inline HierarchySet<Base, Derived...>::BasePtr HierarchySet<Base, Derived...>::findIf(std::function<bool(Base& current)> valid)
{
    auto value_it = std::find_if(m_data.begin(), m_data.end(), [&valid](auto& it) -> bool { return valid(*it); });

    if (value_it != m_data.end())
    {
        return *value_it;
    }

    return nullptr;
}

template<typename Base, typename ...Derived>
inline HierarchySet<Base, Derived...>::ConstBasePtr HierarchySet<Base, Derived...>::findIf(std::function<bool(const Base& current)> valid) const
{
    const auto value_it = std::find_if(m_data.begin(), m_data.end(), [&valid](const auto& it) -> bool { return valid(*it); });

    if (value_it != m_data.end())
    {
        return *value_it;
    }

    return nullptr;
}

} // namespace LunarDB::Moonlight::Implementation
