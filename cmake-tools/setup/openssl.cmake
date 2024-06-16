# CPMAddPackage(
#     NAME OpenSSL
#     VERSION 3.3.1
#     URL https://github.com/openssl/openssl/releases/download/openssl-3.3.1/openssl-3.3.1.tar.gz
#     OPTIONS "OPENSSL_ENABLE_CMAKE ON" "OPENSSL_INCLUDE_LIBRARIES SSL\\\;Crypto"
# )

CPMAddPackage(
    NAME openssl-cmake
    URL https://github.com/jimmy-park/openssl-cmake/archive/main.tar.gz
    OPTIONS "OPENSSL_CONFIGURE_OPTIONS no-shared\\\\;no-tests"
)
