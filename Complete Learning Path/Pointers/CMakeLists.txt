cmake_minimum_required(VERSION 3.22)
project(Pointers C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_executable(Declaration_Usage
        "#1_declaration_&_usage.c"
        src/functions_definitions.c)

add_executable(Dereferencing
        "#2_dereferencing.c")

add_executable(Pointer_Arithmetic
        "#3_pointer_arithmetic.c"
        src/functions_definitions.c)

add_executable(Void_Pointer
        "#4_void_pointer.c"
        src/functions_definitions.c)

include_directories(include)    # Include the include directory
include_directories(src)        # Include the source directory