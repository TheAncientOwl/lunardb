#include "LunarDB/Common/CppExtensions/Timer.hpp"

#include <sstream>

namespace LunarDB::Common::CppExtensions {

Timer::Timer() : m_start{Clock::now()}
{
}

void Timer::reset()
{
    m_start = Clock::now();
}

Timer::TimeUnit Timer::elapsed() const
{
    return std::chrono::duration_cast<Timer::TimeUnit>(Clock::now() - m_start);
}

std::string Timer::elapsedExtended() const
{
    auto elapsed{Clock::now() - m_start};

    auto const hours = std::chrono::duration_cast<std::chrono::hours>(elapsed);
    elapsed -= hours;
    auto const minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsed);
    elapsed -= minutes;
    auto const seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed);
    elapsed -= seconds;
    auto const milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    elapsed -= milliseconds;
    auto const microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
    elapsed -= microseconds;
    auto const nanoseconds = elapsed;

    std::ostringstream oss{};

    oss << hours << ":" << minutes << ":" << seconds << ":" << milliseconds << ":" << microseconds
        << ":" << nanoseconds;

    return oss.str();
}

} // namespace LunarDB::Common::CppExtensions
