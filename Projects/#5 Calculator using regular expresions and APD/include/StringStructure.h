
#ifndef TALLER_1_STRINGSTRUCTURE_H
#define TALLER_1_STRINGSTRUCTURE_H

#include <iostream>
#include <vector>
#include <regex>
#include <sstream>

class StringStructure {
    std::vector<std::string> string; // String composition
    float result; // Result of the operation
    bool isCorrect; // Boolean to check if the string is correct

    public:
    StringStructure(const std::string& expresion, const std::string& delimiters); // Constructor
    std::vector<std::string> getString(); // Return the string
    bool getIsCorrect() const; // Return the boolean isCorrect
    void setIsCorrect(bool isCorrect); // Set the boolean isCorrect
    float getResult() const; // Return the result
    void setResult(float result); // Set the result
    friend std::ostream& operator<<(std::ostream& os, const StringStructure& stringStructure); // Print the string
    static bool validateRegularExpression(const std::string& cadena, const std::string& expresionRegular); // Validate the string with a regular expression
};

#include "../src/StringStructure.hxx"
#endif
