#pragma once

#include "QueryData.hpp"
#include "Primitives.hpp"

#include <variant>

namespace LunarDB::Moonlight::API {

using EQueryType = QueryData::Primitives::EQueryType;

class ParsedQuery
{
public: // methods
    EQueryType type() const;

    template<typename Data>
    Data& get();

    template<typename Data>
    const Data& get() const;

public: // helper
    template<typename Data>
    static ParsedQuery make();

    static ParsedQuery from(std::string_view query);

private: // fields;
    EQueryType m_type;

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

    template<typename>
    struct QueryDataToTypeMap { static const EQueryType value; };
};

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
