#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/Singleton.hpp"

namespace LunarDB::CppExtensions::DesignPatterns::Tests {

struct SomeClass : public Singleton<SomeClass>
{
    int x;
};

TEST(Common_CppExtensions_SingletonTest, dummy)
{
    {
        auto& some_class = SomeClass::Instance();
        some_class.x = 2;
    }

    {
        auto& some_class = SomeClass::Instance();
        EXPECT_EQ(some_class.x, 2);
    }
}

} // namespace LunarDB::CppExtensions::DesignPatterns::Tests