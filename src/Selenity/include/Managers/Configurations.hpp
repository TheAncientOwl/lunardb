#pragma once

#include <filesystem>
#include <string>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/DefinePrimitive.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"
#include "LunarDB/Common/QueryData/QueryData.hpp"

namespace LunarDB::Selenity::API::Managers::Configurations {

// clang-format off
DEFINE_LUNAR_PRIMITIVE(FieldDataType, 
    None = 0,
    Rid = 1,
    String = 2,
    Boolean = 3,
    DateTime = 4,
    Integer = 5,
    Float = 6
)
// clang-format on

namespace Implementation {

struct BaseManagerConfiguration
{
    std::string name{};
    std::filesystem::path home{};
    Common::CppExtensions::UniqueID uid{};

    LUNAR_ENABLE_BINARY_IO(name, home, uid);
};

struct CollectionConfiguration : public BaseManagerConfiguration
{
    enum class ECollectionType
    {
        Undefined,
        Table,
        Document
    };

    struct Schema
    {
    public: // lifecycle
        Schema(Common::QueryData::Schema const& schema);

        Schema() = default;
        ~Schema() = default;
        Schema(Schema const&) = default;
        Schema& operator=(Schema const&) = default;
        Schema(Schema&&) noexcept = default;
        Schema& operator=(Schema&&) noexcept = default;

        bool operator==(Schema const&) const = default;

    public: // fields
        struct Field
        {
            std::string name;
            EFieldDataType type;
            bool nullable;
            bool array;

            bool operator==(Field const&) const = default;

            LUNAR_ENABLE_BINARY_IO(name, type, nullable, array);
        };

        std::vector<Field> fields;

    private: // IO
        LUNAR_ENABLE_BINARY_IO(fields);
    };

    struct Binding
    {
        std::string field;
        Common::CppExtensions::UniqueID collection_uid;

        bool operator==(Binding const&) const = default;

        LUNAR_ENABLE_BINARY_IO(field, collection_uid);
    };

    ECollectionType collection_type;
    Schema schema;
    std::vector<Binding> bindings;

    CollectionConfiguration(
        std::string name,
        std::filesystem::path home,
        Common::CppExtensions::UniqueID uid,
        Common::QueryData::Primitives::EStructureType type,
        std::string const& schema_name,
        std::vector<Common::QueryData::Create::Single::Binding> const& bindings);

    CollectionConfiguration() = default;
    ~CollectionConfiguration() = default;
    CollectionConfiguration(CollectionConfiguration const&) = default;
    CollectionConfiguration& operator=(CollectionConfiguration const&) = default;
    CollectionConfiguration(CollectionConfiguration&&) noexcept = default;
    CollectionConfiguration& operator=(CollectionConfiguration&&) noexcept = default;

    LUNAR_ENABLE_BINARY_IO(name, home, uid, collection_type, schema, bindings);
};

struct ManagerNoConfiguration
{
};

} // namespace Implementation

using DatabaseConfiguration = Implementation::BaseManagerConfiguration;
using CollectionConfiguration = Implementation::CollectionConfiguration;
using NoConfiguration = Implementation::ManagerNoConfiguration;

} // namespace LunarDB::Selenity::API::Managers::Configurations
