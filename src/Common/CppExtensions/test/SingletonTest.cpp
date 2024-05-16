#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/Singleton.hpp"

namespace LunarDB::Common::CppExtensions::DesignPatterns::Tests {

struct SomeClass : public Singleton<SomeClass>
{
    int x;

private:
    LUNAR_SINGLETON_INIT(SomeClass) { x = 5; }
};

TEST(Common_CppExtensions_SingletonTest, dummy)
{
    {
        auto& some_class = SomeClass::Instance();

        EXPECT_EQ(some_class.x, 5);
    }

    {
        auto& some_class = SomeClass::Instance();
        some_class.x = 2;
    }

    {
        auto& some_class = SomeClass::Instance();
        EXPECT_EQ(some_class.x, 2);
    }
}

} // namespace LunarDB::Common::CppExtensions::DesignPatterns::Tests
