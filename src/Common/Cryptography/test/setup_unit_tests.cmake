set(TEST_SUITE_PREFIX Common_Cryptography)

add_lunar_unit_test(
    NAME AES256Test
    SOURCE_FILES test/AES256Test.cpp 
    DEPENDENCIES 
        LunarDB_Common_Cryptography
)
