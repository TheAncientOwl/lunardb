#include "QueryData.hpp"

#include <ostream>

namespace LunarDB::Moonlight::QueryData {

std::ostream& operator<<(std::ostream& os, const Create& rhs)
{
    os << "Create";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Drop& rhs)
{
    os << "Drop";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Migrate& rhs)
{
    os << "Migrate";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Truncate& rhs)
{
    os << "Truncate";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Rename& rhs)
{
    os << "Rename";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Select& rhs)
{
    os << "Select";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Insert& rhs)
{
    os << "Insert";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Update& rhs)
{
    os << "Update";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Delete& rhs)
{
    os << "Delete";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Lock& rhs)
{
    os << "Lock";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Grant& rhs)
{
    os << "Grant";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Revoke& rhs)
{
    os << "Revoke";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Commit& rhs)
{
    os << "Commit";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Rollback& rhs)
{
    os << "Rollback";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const SavePoint& rhs)
{
    os << "SavePoint";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Index& rhs)
{
    os << "Index";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const Database& rhs)
{
    os << "Database";
    // TODO: Provide actual implementation
    return os;
}

std::ostream& operator<<(std::ostream& os, const View& rhs)
{
    os << "View";
    // TODO: Provide actual implementation
    return os;
}

} // namespace LunarDB::Moonlight::QueryData
