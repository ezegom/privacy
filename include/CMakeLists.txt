cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)

file(GLOB DEPENDENCY_INCLUDE_SRC
        "*.h"
        "*.cpp"
        )

add_library(DependencyLib ${DEPENDENCY_INCLUDE_SRC})