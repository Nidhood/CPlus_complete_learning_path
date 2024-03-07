#ifndef TALLER__1_FILEMANAGER_H
#define TALLER__1_FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class FileManager {
    std::string fileDirectory; // File directory
    std::vector<std::vector<std::string>> fileContent; // File content, a matrix of strings, each row is a line of the file and each column is the content of the line.

    public:

    explicit FileManager(std::string fileDirectory); // Constructor.
    std::vector<std::vector<std::string>> read(); // Read the file and store its content in the fileContent attribute making all the lines and words in the file to be stored in a matrix of strings.
    std::vector<std::vector<std::string>> getFileContent(); // Return the file content.
    void printFileContent(); // Print the file content.
};

#include "../src/FileManager.hxx"
#endif