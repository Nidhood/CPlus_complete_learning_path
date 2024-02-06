#include "AFD.h"
#include "FileManager.h"


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
