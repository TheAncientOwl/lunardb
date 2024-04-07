#pragma once

#include "Moonlight/ParsedQuery.hpp"

namespace LunarDB::Moonlight::API {

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
