#include "../include/StringStructure.h"

// Construct the StringStructure object with the string:
StringStructure::StringStructure(const std::string& expresion, const std::string& delimiters) {

    // Initialize the boolean value:
    this->isCorrect = true;

    // Initialize the result:
    this->result = 0.0f;

    // Split the string by the delimiters:
    std::string token;

    // We want to split the string by each delimiter, and store the delimiters in a vector:

    for(int i = 0; i < expresion.size(); i++) {

        // If the expression is not a delimiter, we store it in the token:
        if(delimiters.find(expresion[i]) == std::string::npos) {
            token += expresion[i];
        }

        // If the expression is a delimiter, we store the token and the delimiter in the string vector:
        else {
            for(char delimiter : delimiters) {
                if(expresion[i] == delimiter) {
                    if(!token.empty()) {
                        this->string.push_back(token);
                    }
                    this->string.push_back(std::string(1, delimiter));

                    // Reset the token:
                    token = "";
                }
            }
        }

        // If the expression is the end of the string, we store the token in the string vector:
        if(i == expresion.size() - 1) {
            this->string.push_back(token);
        }
    }
}

// Return the string:
std::vector<std::string> StringStructure::getString() {
    return this->string;
}

// Get the boolean value of the string:
bool StringStructure::getIsCorrect() const {
    return this->isCorrect;
}

// Set the boolean value of the string:
void StringStructure::setIsCorrect(bool isCorrect) {
    this->isCorrect = isCorrect;
}

// Get the result of the string:
float StringStructure::getResult() const {
    return this->result;
}

// Set the result of the string:
void StringStructure::setResult(float result) {
    this->result = result;
}

// Print the string:
std::ostream& operator<<(std::ostream& os, const StringStructure& stringStructure) {
    for(auto & expresion : stringStructure.string) {
        os << expresion << " ";
    }
    return os;
}

// Function to validate a regular expression:
bool StringStructure::validateRegularExpression(const std::string& cadena, const std::string& expresionRegular) {
    std::regex regex(expresionRegular);
    return std::regex_match(cadena, regex);
}