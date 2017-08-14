cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ../accounts
)
file(GLOB accounts 
        "../accounts/*Keys.cpp" 
        "../accounts/*Keys.h"
        )
file(GLOB dependencies 
        "../include/sha256.cpp" 
        "../include/sha256.h"
        "../include/strutils.h"
        "../include/prf.cpp"
        "../include/prf.h"
        )
file(GLOB source_files
        "*.h"
        "*.cpp"
        )

add_executable(Note ${source_files} ${dependencies} ${accounts} )
#${Boost_SYSTEM_LIBRARY}
add_library(NoteLib ${source_files})
target_link_libraries(Note sodium ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})