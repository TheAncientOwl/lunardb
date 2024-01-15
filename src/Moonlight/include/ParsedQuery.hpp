#pragma once

#include <variant>

#include "QueryData/include/QueryData.hpp"

namespace LunarDB::Moonlight::API {

class ParsedQuery
{
public: // methods
    ///
    /// @brief Self explanatory
    ///
    QueryData::Primitives::EQueryType type() const;

    ///
    /// @brief Self explanatory
    ///
    template<typename Data>
    Data& get();

    ///
    /// @brief Self explanatory
    ///
    template<typename Data>
    const Data& get() const;

public: // helpers
    ///
    /// @brief Creates an empty ParsedQuery of given QueryData::Type
    ///
    template<typename Data>
    static ParsedQuery make();

private: // fields;
    QueryData::Primitives::EQueryType m_type;

    std::variant <
        QueryData::Create,
        QueryData::Drop,
        QueryData::Migrate,
        QueryData::Truncate,
        QueryData::Rename,
        QueryData::Select,
        QueryData::Insert,
        QueryData::Update,
        QueryData::Delete,
        QueryData::Lock,
        QueryData::Grant,
        QueryData::Revoke,
        QueryData::Commit,
        QueryData::Rollback,
        QueryData::SavePoint,
        QueryData::Index,
        QueryData::Database,
        QueryData::View,
        QueryData::Rebind,
        QueryData::Schema
    > m_data;

    ///
    /// @brief Used by @c ParsedQuery::make() to decide the QueryData::Type
    /// @tparam T QueryData::Type
    ///
    template<typename T>
    struct QueryDataToTypeMap { static const QueryData::Primitives::EQueryType value; };
};

ParsedQuery parseQuery(std::string_view query);

template<typename Data>
inline Data& ParsedQuery::get()
{
    return std::get<Data>(m_data);
}

template<typename Data>
inline const Data& ParsedQuery::get() const
{
    return std::get<Data>(m_data);
}

template<typename Data>
ParsedQuery ParsedQuery::make()
{
    ParsedQuery query{};
    query.m_type = QueryDataToTypeMap<Data>::value;
    query.m_data = Data{};

    return query;
}

} // namespace LunarDB::Moonlight::API
