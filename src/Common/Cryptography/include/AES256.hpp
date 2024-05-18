#pragma once

#include <cstddef>
#include <vector>

#include "LunarDB/Common/CppExtensions/Singleton.hpp"

namespace LunarDB::Common::Cryptography {

class AES256 : public Common::CppExtensions::DesignPatterns::Singleton<AES256>
{
public:
    using ByteArray = std::vector<unsigned char>;

    ByteArray encrypt(ByteArray const& plaintext);
    ByteArray decrypt(ByteArray const& ciphertext);

    ~AES256();

private:
    LUNAR_SINGLETON_INIT(AES256);

    void handleErrors();

private:
    ByteArray m_key{}; // secret value used by encryption algorithm to transform plaintext to cyphertext and vice versa during decryption
    ByteArray m_iv{}; // initialization vector -> random value used in conjunction with key to ensure
                      // that the same plaintext encrypted with the same key results in different ciphertexts
};

} // namespace LunarDB::Common::Cryptography
