#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>

#define PROVIDE_IMPL_FOR_PODS(MACRO) \
    MACRO(std::int8_t)               \
    MACRO(std::int16_t)              \
    MACRO(std::int32_t)              \
    MACRO(std::int64_t)              \
    MACRO(std::uint8_t)              \
    MACRO(std::uint16_t)             \
    MACRO(std::uint32_t)             \
    MACRO(std::uint64_t)             \
    MACRO(char)                      \
    MACRO(bool)                      \
    MACRO(float)                     \
    MACRO(double)

#define PROVIDE_IMPL_FOR_OBJECTS(MACRO) \
    MACRO(std::string)                  \
    MACRO(std::string_view)

#define PROVIDE_IMPL_FOR(MACRO)  \
    PROVIDE_IMPL_FOR_PODS(MACRO) \
    PROVIDE_IMPL_FOR_OBJECTS(MACRO)

namespace LunarDB::Common::CppExtensions::BinaryIO::Common {

template <typename T>
concept Tuple = requires { std::tuple_size<T>::value; };

template <typename T>
concept HasMakeTuple = requires(T obj) {
    { obj.make_tuple() } -> Tuple;
};

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Common
