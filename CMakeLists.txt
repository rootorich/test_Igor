cmake_minimum_required(VERSION 3.23)
project(lab1)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES
        mylib/*.h
        mylib/*.cpp
        myexeption/*.cpp
        )

add_executable(lab1 ${SOURCES}
        main.cpp)