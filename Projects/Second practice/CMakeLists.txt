cmake_minimum_required(VERSION 3.24)
project(Second_practice C)

set(CMAKE_C_STANDARD 11)

add_executable(Second_practice main.c include/AFD.h src/AFD.c include/FileManager.h src/FileManager.c include/Util.h src/Util.c)

include_directories(include)
include_directories(src)