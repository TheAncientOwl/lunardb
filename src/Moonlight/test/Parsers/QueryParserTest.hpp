#pragma once

#include <gtest/gtest.h>

#include "CppExtensions/include/Errors.hpp"
#include "ParsedQuery.hpp"
#include "QueryData/include/Helpers/Init.hpp"
#include "QueryData/include/Helpers/Operators.hpp"

///
/// @brief Helpers to check success/fail of parsing queries
/// @note QUERY_TYPE macro must be defined per unit in order to use following macros
///

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<QUERY_TYPE>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<QUERY_TYPE>(), CppExtensions::Errors::LunarError)
