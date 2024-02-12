cmake_minimum_required(VERSION 3.24)
project(Proyecto C)

set(CMAKE_C_STANDARD 11)

add_executable(Proyecto main.c src/graph.c)

include_directories(include)
include_directories(src)