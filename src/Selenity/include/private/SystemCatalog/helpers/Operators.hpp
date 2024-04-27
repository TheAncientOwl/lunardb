#pragma once

#include "Selenity/SystemCatalog.hpp"
#include "Selenity/private/SystemCatalog/DatabaseConfig.hpp"

namespace std {

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& rhs)
{
    os << "[ ";
    std::for_each(std::begin(rhs), std::end(rhs), [&os](auto const& value) { os << value << ", "; });
    os << " ]";
    return os;
}

} // namespace std

namespace LunarDB::Selenity::Implementation::SystemCatalog {

std::ostream& operator<<(std::ostream& os, DatabaseConfig const& rhs)
{
    os << "DatabaseConfig{ " << "storage_path: " << rhs.storage_path() << ", name: " << rhs.name()
       << " }";
    return os;
}

} // namespace LunarDB::Selenity::Implementation::SystemCatalog

namespace LunarDB::Selenity::API {

std::ostream& operator<<(std::ostream& os, SystemCatalog const& rhs)
{
    os << "lunar_home: " << rhs.m_lunar_home << ", configs: " << rhs.m_configs
       << ", config_in_use_index: " << rhs.m_config_in_use_index
       << ", config_in_use_index_valid: " << std::boolalpha << rhs.m_config_in_use_index_valid;
    return os;
}

bool surfaceEquals(SystemCatalog const& lhs, SystemCatalog const& rhs)
{
    return lhs.configs() == rhs.configs();
}

} // namespace LunarDB::Selenity::API
