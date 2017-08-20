cmake_minimum_required(VERSION 3.7)
project(PrivateUTXO CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)

find_package(sodium)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem REQUIRED)
# if(Boost_FOUND)c
# include_directories(${Boost_INCLUDE_DIRS})
# endif(Boost_FOUND)
set(BOOST_LIBRARIES
    ${Boost_LESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_definitions(
    # endian.h
    -DHAVE_ENDIAN_H
    -DHAVE_DECL_HTOBE16=1
    -DHAVE_DECL_HTOBE32=1
    -DHAVE_DECL_HTOBE64=1
    -DHAVE_DECL_HTOLE16=1
    -DHAVE_DECL_HTOLE32=1
    -DHAVE_DECL_HTOLE64=1
    -DHAVE_DECL_BE16TOH=1
    -DHAVE_DECL_BE32TOH=1
    -DHAVE_DECL_BE64TOH=1
    -DHAVE_DECL_LE16TOH=1
    -DHAVE_DECL_LE32TOH=1
    -DHAVE_DECL_LE64TOH=1
    # compat.h
    -DHAVE_DECL_STRNLEN
    )

set(ZCASH_DIR /home/eunsoo/privacy/external/zcash)
set(PRIVATEUTXO_DIR /home/eunsoo/privacy)
include_directories(
    ${ZCASH_DIR}/src
    ${ZCASH_DIR}/depends/x86_64-unknown-linux-gnu/include/libsnark
    ${ZCASH_DIR}/depends/x86_64-unknown-linux-gnu/include
    ${PRIVATEUTXO_DIR}
    ${PRIVATEUTXO_DIR}/include
    ${Boost_INCLUDE_DIRS}
    ${sodium_INCLUDE_DIR} 
)

set(TEST_SRC test.cpp)
file(GLOB ZCASH_SRC 
    ${ZCASH_DIR}/src/zcash/IncrementalMerkleTree.cpp
    ${ZCASH_DIR}/src/zcash/IncrementalMerkleTree.hpp
    ${ZCASH_DIR}/src/zcash/util.cpp
    ${ZCASH_DIR}/src/zcash/util.h
    ${ZCASH_DIR}/src/crypto/sha256.cpp
    ${ZCASH_DIR}/src/crypto/sha256.h
    ${ZCASH_DIR}/src/crypto/prf.cpp
    ${ZCASH_DIR}/src/crypto/prf.h
    )
file(GLOB ACCOUNT_INCLUDE 
    ${PRIVATEUTXO_DIR}/accounts/*Keys.h
    # ${PRIVATEUTXO_DIR}/accounts/*Keys.cpp
    )
set(NOTE_INCLUDE
    # ${PRIVATEUTXO_DIR}/note/Note.cpp
    ${PRIVATEUTXO_DIR}/note/Note.h
)

add_executable(merkle_test_zcash
    ${TEST_SRC}
    ${ZCASH_SRC}
    ${ACCOUNT_INCLUDE}
    ${NOTE_INCLUDE}
)
target_link_libraries(merkle_test_zcash
    AccountsLib
    NoteLib
    sodium
    ${BOOST_LIBRARIES}
)