#include "AFD.h"
#include "FileManager.h"

// Conditions to keep in mind:

// For the name, we need to validate the following :
// 1. Name only contains letters.
// 2. Name only can be in minuscule or majuscule.

// For the domain, we need to validate the following:
// 1. Domain only can be in minuscule or majuscule.
// 2. Domain needs to contain a dot.
// 4. Domain cannot contain a dot at the end.
// 5. Domain cannot contain numbers.
// 6. Domain cannot contain special characters, just letters and dots.


int main() {

    // Construct FileManager object:
    FileManager file_manager = setFileManager("../files/test.txt");

    // Read the file (obtain the content):
    read_file(&file_manager);

    // Construct AFD objects:
    AFD *afd = setAFDArray(file_manager.content, file_manager.index);

    // Validate the email addresses:
    for (int i = 0; i < file_manager.index; i++) validate_email(&afd[i]);

    // Free the memory allocated by the file manager:
    free_memory(&file_manager);

    // Free the memory allocated by the AFD array:
    free_memory_afd(afd, file_manager.index);

    // End of the program:
    return 0;
}
