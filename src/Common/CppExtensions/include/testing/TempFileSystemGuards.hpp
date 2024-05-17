#pragma once

#include <cstdio>
#include <filesystem>
#include <gtest/gtest.h>
#include <string_view>

#define AS_STRING_(x) #x
#define AS_STRING(x) AS_STRING_(x)
#define TEMP_FILE "/tmp/lunardb/lunardb_binary_test." AS_STRING(__LINE__) ".tmp"

namespace LunarDB::Common::CppExtensions::Testing::TempFileSystemGuards {

///
/// @brief Utility class: GoogleTest::EXPECT_TRUE(file exists) and deletes file found at given path at the end of its scope.
///
class TempFileGuard
{
public:
    ///
    /// @brief Self explanatory.
    /// @param [in] data -> Path to be checked at the end of the scope.
    ///
    TempFileGuard(std::string_view data) : m_data(data) {}

    ///
    /// @brief Self explanatory.
    ///
    ~TempFileGuard()
    {
        EXPECT_TRUE(std::filesystem::exists(m_data)) << "File does not exists: " << m_data;
        std::remove(m_data.data());
    }

    operator const char*() const { return m_data.data(); }

private:
    std::string_view m_data;
};

///
/// @brief Utility class: GoogleTest::EXPECT_TRUE(directory exists) and deletes directory found at
///        given path at the end of its scope.
///
class TempDirectoryGuard
{
public:
    ///
    /// @brief Self explanatory.
    /// @param [in] data -> Path to be checked at the end of the scope.
    ///
    TempDirectoryGuard(std::filesystem::path data) : m_data(data) {}

    ///
    /// @brief Self explanatory
    ///
    ~TempDirectoryGuard()
    {
        EXPECT_TRUE(std::filesystem::exists(m_data)) << "Directory path does not exist: " << m_data;
        std::filesystem::remove_all(m_data);
    }

    operator std::filesystem::path() const { return m_data; }

private:
    std::filesystem::path m_data;
};

} // namespace LunarDB::Common::CppExtensions::Testing::TempFileSystemGuards
