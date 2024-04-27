#pragma once

#include "Selenity/SystemCatalog.hpp"
#include "Selenity/private/SystemCatalog/DatabaseConfig.hpp"

#define DEFINE_SYSTEM_CATALOG_OSTREAM()

namespace std {

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& rhs)
{
    os << "[ ";
    std::for_each(std::begin(rhs), std::end(rhs), [&os](auto const& value) { os << value << ", "; });
    os << " ]";
    return os;
}

std::ostream& operator<<(
    std::ostream& os,
    LunarDB::Selenity::Implementation::SystemCatalog::DatabaseConfig const& rhs)
{
    os << "storage_path: " << rhs.storage_path() << ", name: " << rhs.name();
    return os;
}

std::ostream& operator<<(std::ostream& os, LunarDB::Selenity::API::SystemCatalog const& rhs)
{
    os << "lunar_home: " << rhs.lunar_home() << ", configs: " << rhs.configs();
    return os;
}

} // namespace std