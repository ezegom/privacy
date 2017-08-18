cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/accounts
)
file(GLOB ACCOUNTS
        "../accounts/*Keys.cpp" 
        "../accounts/*Keys.h"
        )
set(NOTE_DEPENDENCIES
        ${CMAKE_SOURCE_DIR}/include/sha256.cpp 
        ${CMAKE_SOURCE_DIR}/include/sha256.h
        ${CMAKE_SOURCE_DIR}/include/strutils.h
        ${CMAKE_SOURCE_DIR}/include/prf.cpp
        ${CMAKE_SOURCE_DIR}/include/prf.h
        )
file(GLOB NOTE_SRC
        "*.cpp"
        )
file(GLOB NOTE_INCLUDE
        "*.h"
        )
set(NoTE_TEST_SRC
        note_test.cpp
)

# Test Binary
add_executable(NoteTest 
        ${NOTE_TEST_SRC} 
        ${NOTE_INCLUDE}
        ${ACCOUNTS} 
        )
target_link_libraries(NoteTest
        NoteLib 
        sodium 
        ${Boost_FILESYSTEM_LIBRARY} 
        ${Boost_SYSTEM_LIBRARY}
        )
# Library
add_library(NoteLib 
        ${NOTE_SRC}
        ${NOTE_INCLUDE}
        )
target_link_libraries(NoteLib 
        sodium 
        ${Boost_FILESYSTEM_LIBRARY} 
        ${Boost_SYSTEM_LIBRARY}
        AccountsLib
        )