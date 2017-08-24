cmake_minimum_required(VERSION 3.7)
project(PrivateUTXO CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED)

include_directories(
    ../include
    ../
)

set(TEST_SRC test.cpp)
set(MERKLE_INCLUDE
    IncrementalMerkleTree.h
)
set(MERKLE_SRC
    IncrementalMerkleTree.cpp
)
add_library(MerkleTreeLib
    ${MERKLE_SRC}
    ${MERKLE_INCLUDE}
)
target_link_libraries(MerkleTreeLib
    AccountsLib
    NoteLib
    DependencyLib
)

add_executable(MerkleTree_test
    ${TEST_SRC}
)
target_link_libraries(MerkleTree_test
    MerkleTreeLib
    AccountsLib
    NoteLib
    DependencyLib
)