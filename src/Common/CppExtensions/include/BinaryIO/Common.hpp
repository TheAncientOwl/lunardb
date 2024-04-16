#pragma once

#include <iostream>
#include <tuple>
#include <cstddef>
#include <cstdint>

#define PROVIDE_IMPL_FOR(MACRO) \
MACRO(std::int8_t) \
MACRO(std::int16_t) \
MACRO(std::int32_t) \
MACRO(std::int64_t) \
MACRO(std::uint8_t) \
MACRO(std::uint16_t) \
MACRO(std::uint32_t) \
MACRO(std::uint64_t) \

namespace LunarDB::Common::CppExtensions::BinaryIO::Common {

template<typename T>
concept Tuple = requires
{
    std::tuple_size<T>::value;
};

template <typename T>
concept HasMakeTuple = requires(T obj)
{
    { obj.make_tuple() } -> Tuple;
};

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Common
