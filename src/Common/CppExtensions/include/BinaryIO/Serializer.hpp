#pragma once

#include "Common/CppExtensions/BinaryIO/Common.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

namespace Implementation {

template <typename T>
void serialize(std::ostream& os, T const& obj) = delete;

template <typename T>
concept HasSerializeImpl = requires(std::ostream& os, T const& obj) {
    { serialize<T>(os, obj) } -> std::same_as<void>;
};

template <std::size_t Index, typename... Args>
void serializeTuple(std::ostream& os, std::tuple<Args...> const& tuple);

} // namespace Implementation

template <typename T>
    requires Implementation::HasSerializeImpl<T> || Common::IsTuple<T> || Common::HasMakeTuple<T>
void serialize(std::ostream& os, T const& obj);

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer

#include "Common/CppExtensions/private/BinaryIO/Serializer.inl"
