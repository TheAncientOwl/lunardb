#pragma once

#include <cstdio>
#include <filesystem>
#include <gtest/gtest.h>
#include <string_view>

namespace LunarDB::Common::CppExtensions::Testing::TempFileSystemGuards {

class TempFileGuard
{
public:
    TempFileGuard(std::string_view data) : m_data(data) {}
    ~TempFileGuard()
    {
        EXPECT_TRUE(std::filesystem::exists(m_data)) << "File does not exists: " << m_data;
        std::remove(m_data.data());
    }
    operator const char*() const { return m_data.data(); }

private:
    std::string_view m_data;
};

class TempDirectoryGuard
{
public:
    TempDirectoryGuard(std::filesystem::path data) : m_data(data) {}
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
