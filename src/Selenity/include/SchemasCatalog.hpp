#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>

#include "LunarDB/Common/CppExtensions/Singleton.hpp"
#include "LunarDB/Common/QueryData/QueryData.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

namespace LunarDB::Selenity::API {

class SchemasCatalog : public Common::CppExtensions::DesignPatterns::Singleton<SchemasCatalog>
{
public:
    std::filesystem::path getSchemasHomePath() const;

    std::filesystem::path getSchemaFilePath(std::string schema_name) const;

    Common::QueryData::Schema const& getSchema(std::string schema_name);

    void createSchema(Common::QueryData::Schema schema);

    void clearCache();

    ~SchemasCatalog();

private: // singleton
    LUNAR_SINGLETON_INIT(SchemasCatalog);

private: // private API
    void saveSchemaToDisk(Common::QueryData::Schema const& schema) const;
    Common::QueryData::Schema loadSchemaFromDisk(std::string_view schema_name) const;
    void saveToDisk() const;

private:
    std::unordered_map<std::string, Common::QueryData::Schema> m_schemas_cache;
};

} // namespace LunarDB::Selenity::API
