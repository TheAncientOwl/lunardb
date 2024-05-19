#pragma once

#include <filesystem>
#include <string>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/DefinePrimitive.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"

namespace LunarDB::Selenity::Collections {

DEFINE_LUNAR_PRIMITIVE(CollectionType, Unknown = 0, Table = 1, Document = 2)

struct Configuration
{
public: // datastructures
    class Schema
    {
    private: // IO
        LUNAR_ENABLE_BINARY_IO(x);

    private: // fields
        // TODO: Provide implementation
        int x;
    };

public: // fields
    std::string name;
    std::filesystem::path home;
    Common::CppExtensions::UniqueID uid;
    ECollectionType collection_type{ECollectionType::Unknown};
    Schema schema;

private: // IO
    LUNAR_ENABLE_BINARY_IO(name, uid, collection_type, home, schema);
};

} // namespace LunarDB::Selenity::Collections
