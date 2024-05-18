#include <gtest/gtest.h>

#include "LunarDB/Common/Cryptography/AES256.hpp"

using namespace std::string_literals;

namespace LunarDB::Common::Cryptography::Test {

TEST(Common_CppExtensions_Cryptography, AES256)
{
    auto const in_data{"some string   12345 with \nsome text 12302021 \t"s};

    auto const encrypted_data{
        AES256::Instance().encryptAES(AES256::ByteArray(in_data.cbegin(), in_data.cend()))};
    auto const decrypted_data{AES256::Instance().decryptAES(encrypted_data)};

    auto const out_data{std::string(decrypted_data.begin(), decrypted_data.end())};

    std::cout << "\n\t> in_data: \"" << in_data << "\"\n\t> encrypted_data: \""
              << std::string(encrypted_data.begin(), encrypted_data.end())
              << "\"\n\t> decrypted_data: \""
              << std::string(decrypted_data.begin(), decrypted_data.end()) << "\"\n\t> out_data: \""
              << out_data << "\"\n";

    EXPECT_EQ(in_data, out_data);
}

} // namespace LunarDB::Common::Cryptography::Test
