#include "LunarDB/Common/CppExtensions/UniqueID.hpp"

#include <functional>
#include <random>
#include <ranges>
#include <sstream>
#include <utility>

namespace LunarDB::Common::CppExtensions {

UniqueID::UniqueID(UniqueID&& other) noexcept
    : m_data{std::move(other.m_data)}, m_initialized(std::exchange(other.m_initialized, false))
{
}

UniqueID& UniqueID::operator=(UniqueID&& rhs) noexcept
{
    m_data = std::move(rhs.m_data);
    m_initialized = std::exchange(rhs.m_initialized, false);
    return *this;
}

bool UniqueID::operator<(UniqueID const& rhs) const
{
    return m_data < rhs.m_data && m_initialized < rhs.m_initialized;
}

bool UniqueID::operator==(UniqueID const& rhs) const
{
    return m_data == rhs.m_data && m_initialized == rhs.m_initialized;
}

UniqueID UniqueID::generate()
{
    UniqueID out{};
    auto& uuid = out.m_data;

    std::random_device random_device{};
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<std::uint16_t> distribution(0, 255);

    for (auto& byte : uuid)
    {
        byte = distribution(generator);
    }

    // Set version to 4 (0b0100xxxx)
    uuid[6] = (uuid[6] & 0x0F) | 0x40;

    // Set variant to 2 (0b10xxxxxx)
    uuid[8] = (uuid[8] & 0x3F) | 0x80;

    out.m_initialized = true;

    return out;
}

std::string UniqueID::toString() const
{
    if (!m_initialized)
    {
        return "";
    }

    std::ostringstream oss{};

    for (auto const index : std::ranges::iota_view{0u, m_data.size()})
    {
        if (index == 4 || index == 6 || index == 8 || index == 10)
        {
            oss << "-";
        }
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(m_data[index]);
    }

    return oss.str();
}

std::ostream& operator<<(std::ostream& os, UniqueID const& rhs)
{
    return os << rhs.toString();
}

bool UniqueID::initialized() const
{
    return m_initialized;
}

std::size_t UniqueID::Hash::operator()(UniqueID const& uid) const
{
    auto const data_hash{std::hash<std::string>{}(uid.toString())};
    return data_hash ^ (uid.m_initialized << 1);
}

} // namespace LunarDB::Common::CppExtensions
