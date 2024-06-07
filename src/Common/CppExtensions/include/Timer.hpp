#pragma once

#include <chrono>

namespace LunarDB::Common::CppExtensions {

class Timer
{
public:
    Timer();

    void reset();
    std::chrono::microseconds elapsed() const;

private: // fields
    using Clock = std::chrono::_V2::system_clock;

    Clock::system_clock::time_point m_start{};
};

} // namespace LunarDB::Common::CppExtensions
