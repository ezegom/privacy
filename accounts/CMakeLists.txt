cmake_minimum_required(VERSION 3.7)
project(PrivateUTXO CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)
find_package(sodium)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem REQUIRED)



include_directories(${CMAKE_SOURCE_DIR}/include ${sodium_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
if (sodium_FOUND)
    message("[FOUND] Sodium libs at ${sodium_INCLUDE_DIR}")
endif()

file(GLOB dependencies RELATIVE "../include" "*.cpp") #is not working
set(SOURCE_FILES
        main.cpp
        SecretKeys.cpp
        SecretKeys.h
        PublicKeys.cpp
        PublicKeys.h
        ../include/prf.cpp
        ../include/prf.h
        ../include/sha256.cpp
        ../include/sha256.h
        ../include/strutils.h
        ${dependencies}
        )
message(${SOURCE_FILES})
add_executable(Accounts ${SOURCE_FILES})
target_link_libraries(Accounts sodium ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} )

