#pragma once

#include <gtest/gtest.h>

#include "Errors.hpp"
#include "ParsedQuery.hpp"
#include "QueryData/include/helpers/Init.hpp"
#include "QueryData/include/helpers/Operators.hpp"
#include "QueryParser.hpp"

///
/// @brief Helpers to check success/fail of parsing queries
/// @note QUERY_TYPE macro must be defined per unit in order to use following macros
///

#define EXPECT_SUCCESS(query, expected) \
    const auto parsed_query = Moonlight::API::parseQuery(query); \
    const auto& out = parsed_query.get<QUERY_TYPE>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(Moonlight::API::parseQuery(query).get<QUERY_TYPE>(), Moonlight::Errors::ParserError)
