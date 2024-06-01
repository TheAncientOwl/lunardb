#pragma once

#include <iostream>

namespace LunarDB::Common::CppExtensions::ConsoleColorOutput {

std::ostream& dark_blue(std::ostream&);
std::ostream& green(std::ostream&);
std::ostream& dark_aqua(std::ostream&);
std::ostream& dark_red(std::ostream&);
std::ostream& purple(std::ostream&);
std::ostream& gold(std::ostream&);
std::ostream& light_gray(std::ostream&);
std::ostream& dark_gray(std::ostream&);
std::ostream& light_blue(std::ostream&);
std::ostream& lime(std::ostream&);
std::ostream& light_aqua(std::ostream&);
std::ostream& light_red(std::ostream&);
std::ostream& pink(std::ostream&);
std::ostream& yellow(std::ostream&);
std::ostream& white(std::ostream&);
std::ostream& black(std::ostream&);
std::ostream& reset(std::ostream&);

} // namespace LunarDB::Common::CppExtensions::ConsoleColorOutput

#define ccolor LunarDB::Common::CppExtensions::ConsoleColorOutput
