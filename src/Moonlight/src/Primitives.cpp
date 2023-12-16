#include "Primitives.hpp" 
#include "LiteralToStringMap.hpp"

#include <cctype>
#include <stdexcept>

#define MOONLIGHT_PRIMITIVE_CONVERTOR(name, ...) \
namespace name { \
    namespace Internal { \
        const Implementation::LiteralToStringMap<Literal> map{ { \
            __VA_ARGS__ \
        } };\
    } \
    std::string_view toString(Literal literal) { return Internal::map.findByLiteral(literal); } \
    Literal toLiteral(std::string_view str) { return Internal::map.findByString(str); } \
}

namespace LunarDB::Moonlight::QueryData::Primitives {

MOONLIGHT_PRIMITIVE_CONVERTOR(QueryType,
    { Literal::None, "None" },
    { Literal::Create, "Create" },
    { Literal::Drop, "Drop" },
    { Literal::Migrate, "Migrate" },
    { Literal::Truncate, "Truncate" },
    { Literal::Rename, "Rename" },
    { Literal::Select, "Select" },
    { Literal::Insert, "Insert" },
    { Literal::Update, "Update" },
    { Literal::Delete, "Delete" },
    { Literal::Lock, "Lock" },
    { Literal::Grant, "Grant" },
    { Literal::Revoke, "Revoke" },
    { Literal::Commit, "Commit" },
    { Literal::Rollback, "Rollback" },
    { Literal::SavePoint, "SavePoint" },
    { Literal::Index, "Index" },
    { Literal::Database, "Database" },
    { Literal::View, "View" }
)

} // namespace LunarDB::Moonlight::QueryData::Primitives
