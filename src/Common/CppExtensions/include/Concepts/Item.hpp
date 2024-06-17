#pragma once

#include <concepts>

namespace LunarDB::Common::CppExtensions::Concepts {

///
/// @brief Enforces .first and .second members on a type.
///
template <typename T>
concept Item = requires(T t) {
    { t.first } -> std::convertible_to<typename T::first_type>;
    { t.second } -> std::convertible_to<typename T::second_type>;
};

} // namespace LunarDB::Common::CppExtensions::Concepts
