cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)
project(PrivateUTXO CXX)


include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/note
        ${CMAKE_SOURCE_DIR}/accounts
)

file(GLOB TX_INCLUDE *.h )
file(GLOB TX_SRC *.cpp )

# Note library
add_library(TX_LIB
        ${TX_INCLUDE}
        ${TX_SRC}
        )

add_executable(TxTest
        ${TX_INCLUDE}
        ${TX_SRC}
        )

target_link_libraries(
        TxTest
        DependencyLib
)