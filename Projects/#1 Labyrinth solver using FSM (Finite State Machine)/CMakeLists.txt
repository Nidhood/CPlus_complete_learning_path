cmake_minimum_required(VERSION 3.24)
project(First_practice C)

set(CMAKE_C_STANDARD 11)

add_executable(Second_practice main.c src/AdventurerDefinition.c src/MapDefinition.c src/MazeRunnerDefinition.c src/MenusDefinition.c src/Util.c)

include_directories(include)
include_directories(src)