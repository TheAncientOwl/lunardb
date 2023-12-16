#pragma once

#include <string>
#include <tuple>

namespace LunarDB::Moonlight::QueryData {

struct Create {};

struct Drop {};

struct Migrate {};

struct Truncate {};

struct Rename {};

struct Select {};

struct Insert {};

struct Update {};

struct Delete {};

struct Lock {};

struct Grant {};

struct Revoke {};

struct Commit {};

struct Rollback {};

struct SavePoint {};

struct Index {};

struct Database {};

struct View {};

} // namespace LunarDB::Moonlight::QueryData
