#include "../include/FileManager.h"

// Construct the FileManager object with the file directory:
FileManager::FileManager(std::string fileDirectory) {
    this->fileDirectory = std::move(fileDirectory);
    this->fileContent = read();
}

std::vector<std::vector<std::string>> FileManager::read() {

    // First, we need to verify if the file can be opened:
    std::ifstream file(this->fileDirectory);
    if (!file.is_open()) {
        std::cerr << "The file could not be opened." << std::endl;
        return {};
    }

    // Clear fileContent in case the function is called multiple times
    this->fileContent.clear();

    // Read the file and store its content
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> lineContent;
        std::string s;
        while (iss >> s) {
            lineContent.push_back(s);
        }
        this->fileContent.push_back(lineContent);
    }
    file.close(); // Explicitly closing the file is not necessary, but it's okay to do so
    return this->fileContent;
}

// Return the file content:
std::vector<std::vector<std::string>> FileManager::getFileContent() {
    return this->fileContent;
}

// Print the file content:
void FileManager::printFileContent() {
    for (int i = 0; i < this->fileContent.size(); i++) {
        std::cout << "Line #" << (i+1) << ": ";
        for (int j = 0; j < this->fileContent[i].size(); j++) {
            std::cout << this->fileContent[i][j] << " ";
        }
        std::cout << std::endl;
    }
}