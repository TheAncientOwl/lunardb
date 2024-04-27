#include "LunarDB/Selenity/SystemCatalog.hpp"

#include <algorithm>
#include <fstream>

namespace LunarDB::Selenity::API {

SystemCatalog::SystemCatalog(std::filesystem::path lunar_home)
    : m_lunar_home(std::move(lunar_home))
    , m_configs{}
    , m_config_in_use_index{0}
    , m_config_in_use_index_valid{false}
{
    if (!std::filesystem::exists(m_lunar_home))
    {
        std::filesystem::create_directories(m_lunar_home);
    }
}

std::filesystem::path SystemCatalog::getLunarConfigFilePath() const
{
    return m_lunar_home / "lunar_config.ldb";
}

void SystemCatalog::saveToDisk() const
{
    std::ofstream out_file(getLunarConfigFilePath(), std::ios::binary);
    Common::CppExtensions::BinaryIO::Serializer::serialize(out_file, makeTuple());
    out_file.close();
}

void SystemCatalog::loadFromDisk()
{
    std::ifstream in_file(getLunarConfigFilePath(), std::ios::binary);
    auto this_as_tuple{makeTuple()};
    Common::CppExtensions::BinaryIO::Deserializer::deserialize(in_file, this_as_tuple);
    in_file.close();
}

auto SystemCatalog::findDatabaseConfigByName(std::string_view name) const
{
    return std::find_if(std::begin(m_configs), std::end(m_configs), [name](auto const& db_config) {
        return db_config.name() == name;
    });
}

void SystemCatalog::createDatabase(std::string name)
{
    if (findDatabaseConfigByName(name) != std::end(m_configs))
    {
        throw std::runtime_error("Database already exists");
    }

    auto& db_config = m_configs.emplace_back(m_lunar_home / "storage" / name, std::move(name));
    std::filesystem::create_directories(db_config.storage_path());
}

void SystemCatalog::dropDatabase(std::string_view name)
{
    auto const config_it{findDatabaseConfigByName(name)};
    if (config_it == std::end(m_configs))
    {
        throw std::runtime_error("Database does not exist");
    }

    auto const index = config_it - m_configs.begin();
    if (m_config_in_use_index == index)
    {
        m_config_in_use_index_valid = false;
    }

    std::filesystem::remove_all(config_it->storage_path());
    m_configs.erase(config_it);
}

void SystemCatalog::useDatabase(std::string_view name)
{
    auto const config_it{findDatabaseConfigByName(name)};
    if (config_it == std::end(m_configs))
    {
        throw std::runtime_error("Database does not exist");
    }

    m_config_in_use_index = config_it - m_configs.begin();
    m_config_in_use_index_valid = true;
}

bool SystemCatalog::usingDatabase() const
{
    return m_config_in_use_index_valid;
}

} // namespace LunarDB::Selenity::API
