#pragma once

#include "Common/CppExtensions/BinaryIO/Common.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer {

namespace Implementation {

template <typename T>
void deserialize(std::istream& os, T& obj) = delete;

template <typename T>
concept HasDeserializeImpl = requires(std::istream& os, T& obj) {
    { deserialize<T>(os, obj) } -> std::same_as<void>;
};

template <std::size_t Index, typename... Args>
void deserializeTuple(std::istream& is, std::tuple<Args...>& tuple);

} // namespace Implementation

template <typename T>
    requires Implementation::HasDeserializeImpl<T> || Common::IsTuple<T> || Common::HasMakeTuple<T>
void deserialize(std::istream& os, T& obj);

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer

#include "Common/CppExtensions/private/BinaryIO/Deserializer.inl"
