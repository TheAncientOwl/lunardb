#pragma once

#include <array>
#include <filesystem>
#include <forward_list>
#include <span>
#include <string>
#include <string_view>

#include "LunarDB/Common/CppExtensions/BinaryIO/Concepts.hpp"

#define PROVIDE_CONCEPT_DESERIALIZE(Concept) \
    template <typename T>                    \
        requires Concept<T>                  \
    void deserialize(std::istream&, T&)

#define PROVIDE_SPECIALIZED_DESERIALIZE(Type) \
    template <>                               \
    void deserialize(std::istream&, Type&)

#define PROVIDE_TEMPLATE_DESERIALIZE(Type) \
    template <typename T>                  \
    void deserialize(std::istream&, Type<T>&)

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer {

template <typename T>
void deserialize(std::istream&, T&);

PROVIDE_SPECIALIZED_DESERIALIZE(std::string);
PROVIDE_SPECIALIZED_DESERIALIZE(std::filesystem::path);

PROVIDE_CONCEPT_DESERIALIZE(Concepts::Primitive);
PROVIDE_CONCEPT_DESERIALIZE(Concepts::Pair);
PROVIDE_CONCEPT_DESERIALIZE(Concepts::Tuple);
PROVIDE_CONCEPT_DESERIALIZE(Concepts::Tupleable);

template <typename T>
concept AnyContainer =
    Concepts::Container::EmplaceBackable<T> || Concepts::Container::Map::Emplaceable<T> ||
    Concepts::Container::Set::Emplaceable<T>;

PROVIDE_CONCEPT_DESERIALIZE(AnyContainer);

template <typename T>
void deserialize(std::istream&, std::forward_list<T>&);

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer

#include "LunarDB/Common/CppExtensions/private/BinaryIO/Deserializer.inl"
