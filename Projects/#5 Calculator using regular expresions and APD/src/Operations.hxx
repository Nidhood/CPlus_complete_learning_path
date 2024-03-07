#include "../include/Operations.h"

// Add two numbers:
float add(float a, float b) {
    return a + b;
}

// Subtraction two numbers:
float subtraction(float a, float b) {
    return a - b;
}

// Multiplication two numbers:
float multiplication(float a, float b) {
    return a * b;
}

// Division two numbers:
float division(float a, float b) {
    return a / b;
}

// Module two numbers:
int module(int a, int b) {
    return a % b;
}

// Do the operation:
float doOperation(const std::string& operation, float a, float b) {
    if(operation == "+") {
        return add(a, b);
    }
    else if(operation == "-") {
        return subtraction(a, b);
    }
    else if(operation == "*") {
        return multiplication(a, b);
    }
    else if(operation == "/") {
        return division(a, b);
    }
    else if(operation == "%") {
        return module(a, b);
    }
    else {
        return 0.0f;
    }
}
