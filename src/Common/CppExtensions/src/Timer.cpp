#include "LunarDB/Common/CppExtensions/Timer.hpp"

namespace LunarDB::Common::CppExtensions {

Timer::Timer() : m_start{Clock::now()}
{
}

void Timer::reset()
{
    m_start = Clock::now();
}

std::chrono::microseconds Timer::elapsed() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - m_start);
}

} // namespace LunarDB::Common::CppExtensions
