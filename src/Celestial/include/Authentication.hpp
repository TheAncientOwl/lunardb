#pragma once

namespace LunarDB::Celestial::API::Authentication {

class AuthKey
{
public:
    bool operator==(AuthKey const& rhs) const;
};

} // namespace LunarDB::Celestial::API::Authentication
