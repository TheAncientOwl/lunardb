#include "LunarDB/Common/CppExtensions/ConsoleColorOutput.hpp"

namespace LunarDB::Common::CppExtensions::ConsoleColorOutput {

std::ostream& dark_blue(std::ostream& os)
{
    return os << "\033[34m";
}

std::ostream& green(std::ostream& os)
{
    return os << "\033[32m";
}

std::ostream& dark_aqua(std::ostream& os)
{
    return os << "\033[36m";
}

std::ostream& dark_red(std::ostream& os)
{
    return os << "\033[31m";
}

std::ostream& purple(std::ostream& os)
{
    return os << "\033[35m";
}

std::ostream& gold(std::ostream& os)
{
    return os << "\033[33m";
}

std::ostream& light_gray(std::ostream& os)
{
    return os << "\033[37m";
}

std::ostream& dark_gray(std::ostream& os)
{
    return os << "\033[90m";
}

std::ostream& light_blue(std::ostream& os)
{
    return os << "\033[94m";
}

std::ostream& lime(std::ostream& os)
{
    return os << "\033[92m";
}

std::ostream& light_aqua(std::ostream& os)
{
    return os << "\033[96m";
}

std::ostream& light_red(std::ostream& os)
{
    return os << "\033[91m";
}

std::ostream& pink(std::ostream& os)
{
    return os << "\033[95m";
}

std::ostream& yellow(std::ostream& os)
{
    return os << "\033[93m";
}

std::ostream& white(std::ostream& os)
{
    return os << "\033[97m";
}

std::ostream& reset(std::ostream& os)
{
    return os << "\033[0m";
}

} // namespace LunarDB::Common::CppExtensions::ConsoleColorOutput
