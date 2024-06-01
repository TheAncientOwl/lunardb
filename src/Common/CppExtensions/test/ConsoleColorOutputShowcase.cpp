#include <iomanip>
#include <iostream>

#include "LunarDB/Common/CppExtensions/ConsoleColorOutput.hpp"

int main()
{
    using namespace LunarDB::Common::CppExtensions::ConsoleColorOutput;

    static auto constexpr c_label_width{15};
    std::cout << dark_blue << std::setw(c_label_width) << std::left
              << ">> dark_blue: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << green << std::setw(c_label_width) << std::left
              << ">> green: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << dark_aqua << std::setw(c_label_width) << std::left
              << ">> dark_aqua: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << dark_red << std::setw(c_label_width) << std::left
              << ">> dark_red: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << purple << std::setw(c_label_width) << std::left
              << ">> purple: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << gold << std::setw(c_label_width) << std::left
              << ">> gold: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << light_gray << std::setw(c_label_width) << std::left
              << ">> light_gray: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << dark_gray << std::setw(c_label_width) << std::left
              << ">> dark_gray: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << light_blue << std::setw(c_label_width) << std::left
              << ">> light_blue: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << lime << std::setw(c_label_width) << std::left
              << ">> lime: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << light_aqua << std::setw(c_label_width) << std::left
              << ">> light_aqua: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << light_red << std::setw(c_label_width) << std::left
              << ">> light_red: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << pink << std::setw(c_label_width) << std::left
              << ">> pink: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << yellow << std::setw(c_label_width) << std::left
              << ">> yellow: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << white << std::setw(c_label_width) << std::left
              << ">> white: " << "The quick brown fox jumps over the lazy dog." << std::endl;
    std::cout << reset << std::setw(c_label_width) << std::left
              << ">> reset: " << "The quick brown fox jumps over the lazy dog." << std::endl;

    return 0;
}
