cmake_minimum_required(VERSION 3.7)
project(PrivateUTXO CXX)
add_subdirectory(accounts)
add_subdirectory(encryption)
add_subdirectory(note)
add_subdirectory(merkle)
add_subdirectory(iroha-ametsuchi)
include_directories(
        ${PROJECT_SOURCE_DIR}/accounts
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/note
)
