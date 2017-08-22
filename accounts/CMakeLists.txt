cmake_minimum_required(VERSION 3.7)
project(PrivateUTXO CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)

find_package(sodium)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem REQUIRED)

include_directories(
        ${CMAKE_SOURCE_DIR}/include 
        ${sodium_INCLUDE_DIR} 
        ${Boost_INCLUDE_DIRS}
        )

file(GLOB ACCOUNTS_INCLUDE "*Keys.h")
file(GLOB ACCOUNTS_SRC "*Keys.cpp")
set(TEST_SRC main.cpp)

# AccountLib
add_library(AccountsLib        
        ${ACCOUNTS_INCLUDE}
        ${ACCOUNTS_SRC} 
        )
target_link_libraries(AccountsLib 
        sodium 
        ${Boost_FILESYSTEM_LIBRARY} 
        ${Boost_SYSTEM_LIBRARY} 
        DependencyLib
        )
# AccountsLib test
add_executable(Accounts_test
        ${TEST_SRC}
        )
target_link_libraries(Accounts_test
        AccountsLib
        sodium 
        ${Boost_FILESYSTEM_LIBRARY} 
        ${Boost_SYSTEM_LIBRARY} 
        )

