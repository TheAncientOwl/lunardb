#pragma once

#include <ranges>
#include <sstream>

#include "LunarDB/Crescentum/Logger.hpp"

namespace LunarDB::Crescentum::API {

template <typename... Args>
void Logger::log(ELogLevel level, ELunarModule module, Args&&... args)
{
    auto const now{std::chrono::system_clock::now()};
    auto const logging_time{now - m_log_start_time};
    auto const hms{std::chrono::hh_mm_ss{logging_time}};

    std::ostringstream ss{};

    ss << "[" << hms << "] |";
    ss << std::right << std::setw(9) << LogLevel::toString(level) << " |";
    ss << std::right << std::setw(11) << LunarModule::toString(module) << " | ";
    ((ss << std::forward<Args>(args) << " "), ...);
    ss << '\n';

    m_log_queue.push(ss.str());
    m_log_queue_size++;

    static constexpr std::size_t c_max_log_queue_size{25};
    if (m_log_queue_size >= c_max_log_queue_size)
    {
        m_log_queue_size -= c_max_log_queue_size;
        for (auto const _ : std::ranges::iota_view{0u, c_max_log_queue_size})
        {
            m_log << m_log_queue.front();
            m_log_queue.pop();
        }
    }
}

} // namespace LunarDB::Crescentum::API

/// [00:00:00.000005651] |    TRACE |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000043154] |    DEBUG |     Astral | msg1, msg2
/// [00:00:00.000048138] |  WARNING |     Astral | msg1, msg2
/// [00:00:00.000053103] |    ERROR |     Astral | msg1, msg2
/// [00:00:00.000058106] | CRITICAL |     Astral | msg1, msg2
/// [00:00:00.000063795] |    TRACE | BrightMoon | msg1, msg2
/// [00:00:00.000069119] |     INFO | BrightMoon | msg1, msg2
/// [00:00:00.000074069] |    DEBUG | BrightMoon | msg1, msg2
/// [00:00:00.000079301] |  WARNING | BrightMoon | msg1, msg2
/// [00:00:00.000084066] |    ERROR | BrightMoon | msg1, msg2
/// [00:00:00.000088808] | CRITICAL | BrightMoon | msg1, msg2

/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000058106] | CRITICAL |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000079301] |  WARNING | BrightMoon | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000053103] |    ERROR |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2
/// [00:00:00.000036238] |     INFO |     Astral | msg1, msg2