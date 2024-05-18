#pragma once

#include <array>
#include <functional>
#include <ostream>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Common::CppExtensions::Types {

class UniqueID
{
public: // lifecycle
    UniqueID() = default;
    ~UniqueID() = default;
    UniqueID(UniqueID const&) = default;
    UniqueID& operator=(UniqueID const&) = default;
    UniqueID(UniqueID&&) noexcept;
    UniqueID& operator=(UniqueID&&) noexcept;

public: // public API
    ///
    /// @brief Self explanatory
    ///
    static UniqueID generate();

    ///
    /// @brief Self explanatory
    ///
    std::string toString() const;

    ///
    /// @return true if object was created via UniqueID::generate, false otherwise
    ///
    bool initialized() const;

public: // hashing
    struct Hash
    {
        std::size_t operator()(UniqueID const&) const;
    };
    friend std::size_t Hash::operator()(UniqueID const&) const;

private: // IO
    LUNAR_ENABLE_BINARY_IO(m_data, m_initialized);

public: // operators
    bool operator<(UniqueID const&) const;
    bool operator==(UniqueID const&) const;
    friend std::ostream& operator<<(std::ostream&, UniqueID const&);

private: // fields
    std::array<unsigned char, 16> m_data{};
    bool m_initialized{false};
};

} // namespace LunarDB::Common::CppExtensions::Types
