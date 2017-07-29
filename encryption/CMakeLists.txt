cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)
find_package(sodium)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${sodium_INCLUDE_DIR}
)

project(PrivateUTXO CXX)
set(SOURCE_FILES EncryptionKey.cpp EncryptionKey.h Encryptor.cpp Encryptor.h ../include/strutils.h)
add_executable(encryptor main.cpp ${SOURCE_FILES})
target_link_libraries(encryptor sodium)
