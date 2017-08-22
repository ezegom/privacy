cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)

find_package(sodium)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED)

include_directories(
        ../include
        ../
        ${sodium_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
)

file(GLOB ENCRYPTION_SRC
        Encrypt*.cpp
        )
file(GLOB ENCRYPTION_INCLUDE
        Encrypt*.h
)
set(TEST_SRC main.cpp)
add_library(EncryptionLib 
        ${ENCRYPTION_SRC} 
        ${ENCRYPTION_INCLUDE}
        )
target_link_libraries(EncryptionLib
        DependencyLib
)
add_executable(encryptor_test 
        ${TEST_SRC} 
        ${ENCRYPTION_INCLUDE}
        )
target_link_libraries(encryptor_test 
        sodium
        NoteLib
        AccountsLib
        EncryptionLib
        ${Boost_LIBRARIES}
        DependencyLib
        )
