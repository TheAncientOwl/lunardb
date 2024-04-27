#pragma once

#include <gtest/gtest.h>

#include "Common/QueryData/helpers/Init.hpp"
#include "Common/QueryData/helpers/Operators.hpp"
#include "Errors.hpp"
#include "ParsedQuery.hpp"
#include "QueryParser.hpp"

///
/// @brief Helpers to check success/fail of parsing queries.
/// @note QUERY_TYPE macro must be defined per unit in order to use following macros.
///

#define EXPECT_SUCCESS(query, expected)                          \
    auto const parsed_query = Moonlight::API::parseQuery(query); \
    auto const& out = parsed_query.get<QUERY_TYPE>();            \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(Moonlight::API::parseQuery(query).get<QUERY_TYPE>(), Moonlight::Errors::ParserError)
