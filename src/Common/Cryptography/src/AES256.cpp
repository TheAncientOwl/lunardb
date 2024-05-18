#include "LunarDB/Common/Cryptography/AES256.hpp"

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

namespace LunarDB::Common::Cryptography {

LUNAR_SINGLETON_INIT_IMPL(AES256)
{
    OpenSSL_add_all_algorithms();
    ERR_load_CRYPTO_strings();

    m_key.resize(32); // 256-bit key
    m_iv.resize(16); // 128-bit IV

    // TODO: Read key from file
    if (!RAND_bytes(m_key.data(), m_key.size()) || !RAND_bytes(m_iv.data(), m_iv.size()))
    {
        handleErrors();
    }
}

AES256::~AES256()
{
    EVP_cleanup();
    ERR_free_strings();
}

void AES256::handleErrors()
{
    ERR_print_errors_fp(stderr);
    // TODO: Log critical error
}

AES256::ByteArray AES256::encryptAES(ByteArray const& plaintext)
{
    EVP_CIPHER_CTX* ctx;
    std::int32_t len{0};
    std::int32_t ciphertext_len{0};

    ByteArray ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);

    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        handleErrors();
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, m_key.data(), m_iv.data()))
    {
        handleErrors();
    }

    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size()))
    {
        handleErrors();
    }
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len))
    {
        handleErrors();
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);

    return ciphertext;
}

AES256::ByteArray AES256::decryptAES(ByteArray const& ciphertext)
{
    EVP_CIPHER_CTX* ctx;
    std::int32_t len{0};
    std::int32_t plaintext_len{0};

    ByteArray plaintext(ciphertext.size() + EVP_MAX_BLOCK_LENGTH);

    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        handleErrors();
    }

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, m_key.data(), m_iv.data()))
    {
        handleErrors();
    }

    if (1 != EVP_DecryptUpdate(
                 ctx,
                 plaintext.data(),
                 &len,
                 reinterpret_cast<const unsigned char*>(ciphertext.data()),
                 ciphertext.size()))
    {
        handleErrors();
    }
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(plaintext.data()) + len, &len))
    {
        handleErrors();
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    plaintext.resize(plaintext_len);

    return plaintext;
}

} // namespace LunarDB::Common::Cryptography
