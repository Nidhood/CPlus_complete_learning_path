cmake_minimum_required(VERSION 3.22)
project(DMA C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_executable(malloc
        "#1_malloc.c"
        src/dynamic_functions.c)

add_executable(calloc
        "#2_calloc.c"
        src/dynamic_functions.c)

add_executable(realloc
        "#3_realloc.c"
        src/dynamic_functions.c)

include_directories(include)    # Include the include directory
include_directories(src)        # Include the source directory