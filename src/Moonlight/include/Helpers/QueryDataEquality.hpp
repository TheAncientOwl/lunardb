#include "QueryData.hpp"

namespace LunarDB::Moonlight::QueryData {

bool operator==(const Create& lhs, const Create& rhs)
{
    return true;
}

bool operator==(const Drop& lhs, const Drop& rhs)
{
    return true;
}

bool operator==(const Migrate& lhs, const Migrate& rhs)
{
    return true;
}

bool operator==(const Truncate& lhs, const Truncate& rhs)
{
    return true;
}

bool operator==(const Rename& lhs, const Rename& rhs)
{
    return true;
}

bool operator==(const Select& lhs, const Select& rhs)
{
    return true;
}

bool operator==(const Insert& lhs, const Insert& rhs)
{
    return true;
}

bool operator==(const Update& lhs, const Update& rhs)
{
    return true;
}

bool operator==(const Delete& lhs, const Delete& rhs)
{
    return true;
}

bool operator==(const Lock& lhs, const Lock& rhs)
{
    return true;
}

bool operator==(const Grant& lhs, const Grant& rhs)
{
    return true;
}

bool operator==(const Revoke& lhs, const Revoke& rhs)
{
    return true;
}

bool operator==(const Commit& lhs, const Commit& rhs)
{
    return true;
}

bool operator==(const Rollback& lhs, const Rollback& rhs)
{
    return true;
}

bool operator==(const SavePoint& lhs, const SavePoint& rhs)
{
    return true;
}

bool operator==(const Index& lhs, const Index& rhs)
{
    return true;
}

bool operator==(const Database& lhs, const Database& rhs)
{
    return true;
}

bool operator==(const View& lhs, const View& rhs)
{

    return true;
}

} // namespace LunarDB::Moonlight::QueryData
