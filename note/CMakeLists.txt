cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)
project(PrivateUTXO CXX)


include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ../
)

file(GLOB source_files
        "*.h"
        "*.cpp")

add_executable(Note ${source_files})