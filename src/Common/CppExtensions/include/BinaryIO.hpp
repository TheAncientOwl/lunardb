#pragma once

#include "LunarDB/Common/CppExtensions/BinaryIO/Deserializer.hpp"
#include "LunarDB/Common/CppExtensions/BinaryIO/Serializer.hpp"

///
/// @brief Provide binary serialize friend function signature.
///
#define LUNAR_ENABLE_BINARY_SERIALIZER()                                          \
    template <typename T>                                                         \
        requires LunarDB::Common::CppExtensions::BinaryIO::Concepts::Tupleable<T> \
    friend void LunarDB::Common::CppExtensions::BinaryIO::Serializer::serialize(  \
        std::ostream& os, T const& tupleable);

///
/// @brief Provide binary deserialize friend function signature.
///
#define LUNAR_ENABLE_BINARY_DESERIALIZER()                                           \
    template <typename T>                                                            \
        requires LunarDB::Common::CppExtensions::BinaryIO::Concepts::Tupleable<T>    \
    friend void LunarDB::Common::CppExtensions::BinaryIO::Deserializer::deserialize( \
        std::istream& is, T& tupleable)

///
/// @brief Provide makeTuple() and makeTuple() const variants required by
///        @c LunarDB::Common::CppExtensions::BinaryIO::serialize.
/// @param [in] List of desired fields to be binary serialized/deserialized
///
#define LUNAR_ENABLE_BINARY_IO(...)   \
    inline auto makeTuple()           \
    {                                 \
        return std::tie(__VA_ARGS__); \
    }                                 \
    inline auto makeTuple() const     \
    {                                 \
        return std::tie(__VA_ARGS__); \
    }                                 \
    LUNAR_ENABLE_BINARY_SERIALIZER()  \
    LUNAR_ENABLE_BINARY_DESERIALIZER()
