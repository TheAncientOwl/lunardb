#include "QueryData.hpp"

namespace LunarDB::Moonlight::QueryData {

bool operator==(const Create& lhs, const Create& rhs)
{
    const auto reduce = [](const Create& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Drop& lhs, const Drop& rhs)
{
    const auto reduce = [](const Drop& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Migrate& lhs, const Migrate& rhs)
{
    const auto reduce = [](const Migrate& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Truncate& lhs, const Truncate& rhs)
{
    const auto reduce = [](const Truncate& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Rename& lhs, const Rename& rhs)
{
    const auto reduce = [](const Rename& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Select& lhs, const Select& rhs)
{
    const auto reduce = [](const Select& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Insert& lhs, const Insert& rhs)
{
    const auto reduce = [](const Insert& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Update& lhs, const Update& rhs)
{
    const auto reduce = [](const Update& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Delete& lhs, const Delete& rhs)
{
    const auto reduce = [](const Delete& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Lock& lhs, const Lock& rhs)
{
    const auto reduce = [](const Lock& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Grant& lhs, const Grant& rhs)
{
    const auto reduce = [](const Grant& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Revoke& lhs, const Revoke& rhs)
{
    const auto reduce = [](const Revoke& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Commit& lhs, const Commit& rhs)
{
    const auto reduce = [](const Commit& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Rollback& lhs, const Rollback& rhs)
{
    const auto reduce = [](const Rollback& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const SavePoint& lhs, const SavePoint& rhs)
{
    const auto reduce = [](const SavePoint& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Index& lhs, const Index& rhs)
{
    const auto reduce = [](const Index& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const Database& lhs, const Database& rhs)
{
    const auto reduce = [](const Database& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

bool operator==(const View& lhs, const View& rhs)
{

    const auto reduce = [](const View& obj) { return true; };

    return reduce(lhs) == reduce(rhs);
}

} // namespace LunarDB::Moonlight::QueryData
