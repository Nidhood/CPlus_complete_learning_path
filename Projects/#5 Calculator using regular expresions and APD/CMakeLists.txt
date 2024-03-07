cmake_minimum_required(VERSION 3.27)
project(Taller__1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Taller__1
        main.cpp
        src/FileManager.hxx
        src/StringStructure.hxx
        src/Operations.hxx
        src/Exercises.hxx)

include_directories(/include)
include_directories(/src)
