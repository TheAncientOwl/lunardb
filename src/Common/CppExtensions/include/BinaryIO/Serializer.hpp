#pragma once

#include <filesystem>
#include <forward_list>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "LunarDB/Common/CppExtensions/BinaryIO/Concepts.hpp"

#define PROVIDE_CONCEPT_SERIALIZE(Concept) \
    template <typename T>                  \
        requires Concept<T>                \
    void serialize(std::ostream&, T const&)

#define PROVIDE_SPECIALIZED_SERIALIZE(Type) \
    template <>                             \
    void serialize(std::ostream&, Type const&)

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

template <typename T>
void serialize(std::ostream&, T const&);

PROVIDE_SPECIALIZED_SERIALIZE(std::string);
PROVIDE_SPECIALIZED_SERIALIZE(std::string_view);
PROVIDE_SPECIALIZED_SERIALIZE(std::filesystem::path);

PROVIDE_CONCEPT_SERIALIZE(Concepts::Primitive);
PROVIDE_CONCEPT_SERIALIZE(Concepts::Pair);
PROVIDE_CONCEPT_SERIALIZE(Concepts::Tuple);
PROVIDE_CONCEPT_SERIALIZE(Concepts::Tupleable);
PROVIDE_CONCEPT_SERIALIZE(Concepts::IterableSerializable);

template <typename T>
void serialize(std::ostream&, std::forward_list<T> const&);

template <typename T>
void serialize(std::ostream&, std::forward_list<T> const&, typename std::forward_list<T>::size_type);

template <typename T>
void serialize(std::ostream&, std::optional<T> const&);

template <typename T>
void serialize(std::ostream&, std::shared_ptr<T> const&);

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer

#include "LunarDB/Common/CppExtensions/private/BinaryIO/Serializer.inl"
