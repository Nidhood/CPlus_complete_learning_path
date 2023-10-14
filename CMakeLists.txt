cmake_minimum_required(VERSION 3.24)
project(intelli C)

set(CMAKE_C_STANDARD 11)

add_executable(intelli app/main.c src/AdventurerDefinition.c src/MapDefinition.c src/MazeRunnerDefinition.c src/MenusDefinition.c src/Util.c)
