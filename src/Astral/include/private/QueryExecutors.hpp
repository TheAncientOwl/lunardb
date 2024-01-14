#pragma once

#include "Moonlight/include/ParsedQuery.hpp"
#include "Astral/include/QueryExecutor.hpp"

#define PROVIDE_QUERY_EXECUTOR(Specialization) \
namespace Specialization { \
[[nodiscard]] ExecutorBundle makeBundle(); \
void execute(const Moonlight::API::ParsedQuery& parsed_query, const Astral::API::QueryExecutor::Config& config); \
}

#define PROVIDE_QUERY_EXECUTOR_IMPL(Specialization) \
ExecutorBundle Specialization::makeBundle() { return std::make_pair(QueryData::Primitives::EQueryType::Specialization, Specialization::execute); } \
void Specialization::execute(const Moonlight::API::ParsedQuery& parsed_query, const Astral::API::QueryExecutor::Config& config)

#define DECLARE_QUERY_OBJECT(type) \
const auto query = parsed_query.get<QueryData::type>();

namespace LunarDB::Astral::Implementation {

using Executor = void(*)(const Moonlight::API::ParsedQuery&, const Astral::API::QueryExecutor::Config&);
using ExecutorBundle = std::pair<QueryData::Primitives::EQueryType, Executor>;

PROVIDE_QUERY_EXECUTOR(Create)

} // namespace LunarDB::Astral::Implementation
