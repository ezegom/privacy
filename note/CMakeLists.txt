cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}
)
file(GLOB NOTE_INCLUDE *.h )
file(GLOB NOTE_SRC *.cpp )
set(TEST_SRC note_test.cpp)

# Note library
add_library(NoteLib 
        ${NOTE_INCLUDE}
        ${NOTE_SRC}
        )
target_link_libraries(NoteLib
        sodium 
        ${Boost_FILESYSTEM_LIBRARY}     
        ${Boost_SYSTEM_LIBRARY}
        )
        
# Note test binary
add_executable(Note_test
        ${TEST_SRC}
        )
target_link_libraries(Note_test
        NoteLib
        AccountsLib
)