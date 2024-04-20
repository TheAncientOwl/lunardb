#pragma once

#include "Common/CppExtensions/BinaryIO/Common.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

namespace Internal {

template <typename T>
void serialize(std::ostream& os, T const& obj) = delete;

template <typename T>
    requires Common::Concepts::Enum<T>
void serializeEnum(std::ostream& os, T const& obj);

template <typename First, typename Second>
void serializePair(std::ostream& os, std::pair<First, Second> const& pair);

template <std::size_t Index, typename... Args>
void serializeTuple(std::ostream& os, std::tuple<Args...> const& tuple);

template <typename T>
    requires Common::Concepts::Container<T>
void serializeContainer(std::ostream& os, T const& container);

template <typename T>
concept Serializable = requires(std::ostream& os, T obj) {
    { Internal::serialize<T>(os, obj) } -> std::same_as<void>;
};

} // namespace Internal

template <typename T>
concept Serializable =
    Internal::Serializable<T> || Common::Concepts::Enum<T> || Common::Concepts::Pair<T> ||
    Common::Concepts::Tuple<T> || Common::Concepts::Tupleable<T> || Common::Concepts::Container<T>;

template <typename T>
    requires Serializer::Serializable<T>
void serialize(std::ostream& os, T const& obj);

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer

#include "Common/CppExtensions/private/BinaryIO/Serializer.inl"
