cmake_minimum_required(VERSION 3.7)
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
        ../
)

file(GLOB source_files
        "*.h"
        "*.cpp")

add_executable(encryptor main.cpp ${source_files})
target_link_libraries(encryptor sodium AccountsLib NoteLib  ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
