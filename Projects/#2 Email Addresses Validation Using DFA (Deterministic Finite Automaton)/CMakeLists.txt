cmake_minimum_required(VERSION 3.24)
project(Second_practice C)

set(CMAKE_C_STANDARD 11)

add_executable(Second_practice main.c src/AFD.c src/FileManager.c src/Util.c)

include_directories(include)
include_directories(src)