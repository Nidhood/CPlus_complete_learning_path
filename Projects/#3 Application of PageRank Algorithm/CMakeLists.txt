cmake_minimum_required(VERSION 3.24)
project(Proyecto C)

set(CMAKE_C_STANDARD 11)

add_executable(Proyecto
        main.c
        src/GraphDefinition.c
        src/TransitionMatrixDefinition.c
        src/MatrixOperationsDefinition.c
        src/PageRankAlgorithmDefinition.c
        src/NumberNameEquivalenceDefinition.c
        src/AdjacencyMatrixDefinition.c
        src/MetricsDefinition.c)

include_directories(include)
include_directories(src)