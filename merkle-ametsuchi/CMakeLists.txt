cmake_minimum_required(VERSION 3.7)
project(PrivateUTXO CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)
find_package(sodium)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem REQUIRED)

set(AMETSUCHI_DIR /home/eunsoo/privacy/external/iroha-ametsuchi)

set(AMETSUCHI_INCLUDE 
        ${AMETSUCHI_DIR}/include
        ${AMETSUCHI_DIR}/schema
        )
set(AMETSUCHI_SRC
        ${AMETSUCHI_DIR}/src/ametsuchi
        ${AMETSUCHI_DIR}/src/ametsuchi/merkle_tree
        
)
set(EXTERNAL_INCLUDE
        ${AMETSUCHI_DIR}/external/src/google_flatbuffers/include
        ${AMETSUCHI_DIR}/external/src/lmdb_LMDB/libraries/liblmdb
        ${AMETSUCHI_DIR}/external/src/gvanas_keccak/bin/generic64/libkeccak.a.headers
        )
include_directories(
        ${CMAKE_SOURCE_DIR}/include 
        ${sodium_INCLUDE_DIR} 
        ${Boost_INCLUDE_DIRS}
        ${AMETSUCHI_INCLUDE}
        ${EXTERNAL_INCLUDE}
        ../accounts
        ../note
        )


file(GLOB dependencies 
        "../include/*.cpp" 
        "../include/*.h"
        )

file(GLOB source_files
        "*.cpp"
        "*.h"
        )

add_executable(merkle_test_ametsuchi
        ${source_files} 
        ${dependencies}
        ${AMETSUCHI_INCLUDE}
        ${AMETSUCHI_SRC}
        )
add_dependencies(merkle_test_ametsuchi
        ametsuchi
        AccountsLib
        NoteLib
)
target_link_libraries(merkle_test_ametsuchi
        ${Boost_FILESYSTEM_LIBRARY} 
        ${Boost_SYSTEM_LIBRARY}
        sodium 
        ametsuchi
        AccountsLib
        NoteLib      
        )
        
add_library(MerkleLib 
        ${source_files} 
        ${dependencies}
        )
target_link_libraries(MerkleLib 
        sodium 
        ${Boost_FILESYSTEM_LIBRARY} 
        ${Boost_SYSTEM_LIBRARY} 
        )
add_dependencies(MerkleLib
        ametsuchi
)

