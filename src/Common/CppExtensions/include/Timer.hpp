#pragma once

#include <chrono>
namespace LunarDB::Common::CppExtensions {

class Timer
{
public:
    using TimeUnit = std::chrono::nanoseconds;

public:
    Timer();

    void reset();
    TimeUnit elapsed() const;
    std::string elapsedExtended() const;

private: // fields
    using Clock = std::chrono::_V2::system_clock;

    Clock::system_clock::time_point m_start{};
};

} // namespace LunarDB::Common::CppExtensions
