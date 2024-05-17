#include "LunarDB/Selenity/SystemCatalog.hpp"

#include <algorithm>
#include <fstream>

namespace LunarDB::Selenity::API {

LUNAR_SINGLETON_INIT_IMPL(SystemCatalog)
{
    loadFromDisk();
}

std::filesystem::path SystemCatalog::getLunarHomePath() const
{
    // TODO: Get path from config.
    // !NOTE: This is not windows compatible? config path should fix this.
    static std::filesystem::path const c_lunar_home{"/tmp/lunardb"};

    if (!std::filesystem::exists(c_lunar_home))
    {
        std::filesystem::create_directories(c_lunar_home);
    }

    return c_lunar_home;
}

std::filesystem::path SystemCatalog::getLunarConfigFilePath() const
{
    static auto const c_lunar_config_file_path{getLunarHomePath() / "lunar_config.ldb"};
    return c_lunar_config_file_path;
}

void SystemCatalog::saveToDisk() const
{
    std::ofstream out_file(getLunarConfigFilePath(), std::ios::binary);
    Common::CppExtensions::BinaryIO::Serializer::serialize(out_file, makeTuple());
    out_file.close();
}

void SystemCatalog::loadFromDisk()
{
    clear();

    std::ifstream in_file(getLunarConfigFilePath(), std::ios::binary);
    auto this_as_tuple{makeTuple()};
    Common::CppExtensions::BinaryIO::Deserializer::deserialize(in_file, this_as_tuple);
    in_file.close();
}

auto SystemCatalog::findDatabaseConfigByName(std::string_view name) const
{
    return std::find_if(std::begin(m_configs), std::end(m_configs), [name](auto const& db_config) {
        return db_config.getName() == name;
    });
}

void SystemCatalog::createDatabase(std::string name)
{
    if (findDatabaseConfigByName(name) != std::end(m_configs))
    {
        throw std::runtime_error("Database already exists");
    }

    auto& db_config = m_configs.emplace_back(getLunarHomePath() / "storage" / name, std::move(name));
    std::filesystem::create_directories(db_config.getHomePath());
}

void SystemCatalog::dropDatabase(std::string_view name)
{
    auto const config_it{findDatabaseConfigByName(name)};
    if (config_it == std::end(m_configs))
    {
        throw std::runtime_error("Database does not exist");
    }

    if (static_cast<bool>(m_config_in_use_index) && config_it - m_configs.begin() == 0)
    {
        m_config_in_use_index = std::nullopt;
    }

    std::filesystem::remove_all(config_it->getHomePath());
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
}

bool SystemCatalog::usingDatabase() const
{
    return static_cast<bool>(m_config_in_use_index);
}

void SystemCatalog::clear()
{
    m_configs.clear();
    m_config_in_use_index = std::nullopt;
}

SystemCatalog::~SystemCatalog()
{
    saveToDisk();
}

std::optional<std::filesystem::path> SystemCatalog::getDatabaseInUseHomePath() const
{
    if (static_cast<bool>(m_config_in_use_index))
    {
        return m_configs[*m_config_in_use_index].getHomePath();
    }

    return std::nullopt;
}

} // namespace LunarDB::Selenity::API
