//
// Created by Ivan Dario Orozco Ibañez on 6/02/24.
//

#ifndef SECOND_PRACTICE_FILEMANAGER_H
#define SECOND_PRACTICE_FILEMANAGER_H

#include <stdio.h> // Include the standard input/output library.
#include <stdbool.h> // Include the boolean library.
#include <string.h> // Include the string library.
#include <stdlib.h> // Include the standard library.

// Declare the structure:
typedef struct {
    const char* line;
} Content;

typedef struct {
    char* file_name;
    int index;
    Content *content;
} FileManager;

// Declare functions:

// Set the FileManager object (constructor):
FileManager setFileManager( const char* file_name );

// Read the file:
void read_file( FileManager *file_manager );

// Free the memory allocated by the file manager:
void free_memory( FileManager *file_manager );

#endif //SECOND_PRACTICE_FILEMANAGER_H
