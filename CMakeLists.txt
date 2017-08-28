cmake_minimum_required(VERSION 3.7)
project(PrivateUTXO CXX)

# default build type debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(CMAKE_BUILD_TYPE)

# default cxx_standard c++14
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(accounts)
add_subdirectory(encryption)
add_subdirectory(note)
add_subdirectory(merkle)
add_subdirectory(include)
add_subdirectory(transaction)
