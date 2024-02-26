cmake_minimum_required(VERSION 3.24)
project(_4_Email_Address_Validation_using_AFND C)

set(CMAKE_C_STANDARD 11)

add_executable(Third_practice main.c src/AFD.c src/FileManager.c src/Util.c src/graph.c)

include_directories(include)
include_directories(src)
