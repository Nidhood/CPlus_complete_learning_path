cmake_minimum_required(VERSION 3.24)
project(Proyecto C)

set(CMAKE_C_STANDARD 11)

add_executable(Proyecto
        main.c
        src/GraphDefinition.c
        src/AdjacencyMatrixDefinition.c
        src/MatrixOperationsDefinition.c
        src/PageRankAlgorithmDefinition.c
        src/NumberNameEquivalenceDefinition.c)

include_directories(include)
include_directories(src)