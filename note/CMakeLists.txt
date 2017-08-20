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
file(GLOB accounts 
        "${CMAKE_SOURCE_DIR}/accounts/*Keys.cpp" 
        "${CMAKE_SOURCE_DIR}/accounts/*Keys.h"
        )
file(GLOB dependencies 
        "${CMAKE_SOURCE_DIR}/include/sha256.cpp" 
        "${CMAKE_SOURCE_DIR}/include/sha256.h"
        "${CMAKE_SOURCE_DIR}/include/strutils.h"
        "${CMAKE_SOURCE_DIR}/include/prf.cpp"
        "${CMAKE_SOURCE_DIR}/include/prf.h"
        )
file(GLOB source_files
        "*.h"
        "*.cpp"
        )

add_executable(Note 
        ${source_files} 
        ${dependencies} 
        ${accounts} 
        )
#${Boost_SYSTEM_LIBRARY}
add_library(NoteLib ${source_files})
target_link_libraries(Note 
        sodium 
        ${Boost_FILESYSTEM_LIBRARY}     
        ${Boost_SYSTEM_LIBRARY}
        )