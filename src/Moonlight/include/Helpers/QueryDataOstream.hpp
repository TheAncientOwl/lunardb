#include "QueryData.hpp"

#include <ostream>

namespace LunarDB::Moonlight::QueryData {

std::ostream& operator<<(std::ostream& os, const Create& rhs)
{
    os << "Create";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Drop& rhs)
{
    os << "Drop";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Migrate& rhs)
{
    os << "Migrate";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Truncate& rhs)
{
    os << "Truncate";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Rename& rhs)
{
    os << "Rename";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Select& rhs)
{
    os << "Select";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Insert& rhs)
{
    os << "Insert";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Update& rhs)
{
    os << "Update";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Delete& rhs)
{
    os << "Delete";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Lock& rhs)
{
    os << "Lock";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Grant& rhs)
{
    os << "Grant";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Revoke& rhs)
{
    os << "Revoke";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Commit& rhs)
{
    os << "Commit";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Rollback& rhs)
{
    os << "Rollback";
    return os;
}

std::ostream& operator<<(std::ostream& os, const SavePoint& rhs)
{
    os << "SavePoint";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Index& rhs)
{
    os << "Index";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Database& rhs)
{
    os << "Database";
    return os;
}

std::ostream& operator<<(std::ostream& os, const View& rhs)
{
    os << "View";
    return os;
}

} // namespace LunarDB::Moonlight::QueryData
