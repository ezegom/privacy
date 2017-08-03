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

file(GLOB dependencies "../include/*.cpp" "../include/*.cpp")

file(GLOB source_files
        "*.cpp"
        "*.h")

add_executable(Accounts ${source_files} ${dependencies})
add_library(AccountsLib ${source_files} ${dependencies})

target_link_libraries(Accounts sodium ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} )

