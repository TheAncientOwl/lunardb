# OpenSSL for macOS
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    # assert that Homebrew is available
    find_program(HOMEBREW_EXECUTABLE brew)

    if(HOMEBREW_EXECUTABLE)
        message(STATUS "Homebrew found")
    else()
        message(FATAL_ERROR "Homebrew was not found")
    endif()

    # now find OpenSSL installation path
    execute_process(
        COMMAND brew --prefix openssl@1.1
        RESULT_VARIABLE BREW_OPENSSL
        OUTPUT_VARIABLE BREW_OPENSSL_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # set these variables so cmake can find the package config, headers etc ..
    if(BREW_OPENSSL EQUAL 0 AND EXISTS "${BREW_OPENSSL_PREFIX}")
        set(OPENSSL_ROOT_DIR BREW_OPENSSL_PREFIX)
        set(OPENSSL_INCLUDE_DIR "${BREW_OPENSSL_PREFIX}/include")
        set(OPENSSL_LIBRARIES "${BREW_OPENSSL_PREFIX}/lib")
        set(OPENSSL_CRYPTO_LIBRARY "${BREW_OPENSSL_PREFIX}/lib/libcrypto.dylib")
    endif()
endif()

find_package(OpenSSL REQUIRED)
