//
// Created by Ivan Dario Orozco Ibanez on 6/02/24.
//

#include "FileManager.h"

// Define the function:

// Set the FileManager object (constructor):
FileManager setFileManager(const char* file_name) {
    FileManager file_manager;
    file_manager.file_name = strdup(file_name);
    file_manager.index = 0;
    file_manager.content = NULL;
    return file_manager;
}

// Read the file:
void read_file(FileManager *file_manager) {
    FILE *file = fopen(file_manager->file_name, "r");
    if (file == NULL) {
        printf("Error: The file could not be opened.\n");
    } else {
        char *line = NULL;
        size_t line_length = 0;
        file_manager->content = NULL;
        while (getline(&line, &line_length, file) != -1) {

            // We don't have the precise number of lines, so we need to reallocate the memory (the same as the vector in C++):
            file_manager->content = realloc(file_manager->content, sizeof(Content) * (file_manager->index + 1));
            if (file_manager->content == NULL) {
                printf("Error: Memory allocation failed.\n");
                fclose(file);
                free(line);
                return;
            }
            file_manager->content[file_manager->index].line = strdup(line);
            file_manager->index++;
        }
        fclose(file);
        free(line);
    }
}
// Free the memory allocated by the file manager (Very important to avoid memory leaks):
void free_memory(FileManager *file_manager) {
    for (int i = 0; i < file_manager->index; i++) {
        free((void*)file_manager->content[i].line);
    }
    free(file_manager->content);
    free(file_manager->file_name);
}
