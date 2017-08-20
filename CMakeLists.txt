cmake_minimum_required(VERSION 3.7)
project(PrivateUTXO CXX)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug)
endif(CMAKE_BUILD_TYPE)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(accounts)
add_subdirectory(encryption)
add_subdirectory(note)
add_subdirectory(merkle-ametsuchi)
add_subdirectory(merkle-zcash)
add_subdirectory(external/iroha-ametsuchi)
include_directories(
        ${PROJECT_SOURCE_DIR}/accounts
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/note
)
