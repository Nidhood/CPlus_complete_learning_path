#include "../include/Exercises.h"

// Do the exercise 3:
void exercise3() {

    // Declare counter for the number of lines:
    int counter = 0;

    // Auxiliary strings vector to modify the queue:
    std::string aux_string, aux_string2;

    // Declare the delimiters for the string:
    std::string delimiters = "+-";

    // Aux string to store the operation:
    std::string operation;

    // Aux float number to store the expressions:
    float number1 = 0.0f, number2 = 0.0f;

    // Declare the strings vector to be analyzed:
    std::vector<StringStructure> strings;

    // Print the exercise:
    std::cout << "\nExercise 3: " << std::endl << std::endl;;

    // Declare the file manager object:
    FileManager fileManager("../test_files/test_third_point.txt");

    // Grab each line of the file, separate each word by the selected delimiters:
    for(auto & line : fileManager.getFileContent()) {
        for(auto & word : line) {

            // Here we are using the StringStructure class to store the word and the delimiter:
            strings.push_back(StringStructure(word, delimiters));
        }
    }

    // We are going to use a queue to do the operations and validate the correct format:
    std::queue<std::string> queue;

    // Now we are going to do the operations:
    for(auto & string : strings) {

        if(string.getString().size() < 3) {
            string.setIsCorrect(false);
            continue;
        }
        for(auto & expresion : string.getString()) {

                // If the expresion is a number, we validate it and store it in the queue:
                if(string.validateRegularExpression(expresion, "[0-9]+(\\.[0-9]+)?")) {

                    // If in the head of the queue is an operation, we store the number under the operation:
                    if(queue.size() > 0 && string.validateRegularExpression(queue.front(), "[" + delimiters + "]")) {
                        aux_string = queue.front();
                        queue.pop();
                        aux_string2 = queue.front();
                        queue.pop();
                        queue.push(aux_string);
                        queue.push(aux_string2);
                        queue.push(expresion);
                    } else {
                        queue.push(expresion);
                    }

                // If the expresion is a delimiter, we validate it and apply the operation:
                } else if(string.validateRegularExpression(expresion, "[" + delimiters + "]")) {

                    // Firs we need to verify that have at least one number in the queue:
                    if(queue.size() < 1) {
                        string.setIsCorrect(false);

                        // Restart the queue:
                        while(!queue.empty()) {
                            queue.pop();
                        }

                        // We break the loop:
                        break;
                    }

                    // Now we are going to put the operation in head of the queue, first save the number in the queue:
                    aux_string = queue.front();

                    // Remove the number from the queue:
                    queue.pop();

                    // Put the operation in the queue:
                    queue.push(expresion);

                    // Put the numbers in the queue:
                    queue.push(aux_string);

                }
                else{
                    string.setIsCorrect(false);

                    // Restart the queue:
                    while(!queue.empty()) {
                        queue.pop();
                    }

                    break;
                }

                // Now we are going to operate the numbers in the queue:
                if(string.validateRegularExpression(queue.front(), "[" + delimiters + "]") && queue.size() > 2) {

                    // Grab the operation in the queue:
                    operation = queue.front();

                    // Remove the operation from the queue:
                    queue.pop();

                    // Grab the first number in the queue:
                    number1 = std::stof(queue.front());

                    // Remove the first number from the queue:
                    queue.pop();

                    // Grab the second number in the queue:
                    number2 = std::stof(queue.front());

                    // Remove the second number from the queue:
                    queue.pop();

                    // Do the operation and store the result in the queue:
                    string.setResult(doOperation(operation, number1, number2));
                } else if(queue.size() > 3){

                    // Restart the queue:
                    while(!queue.empty()) {
                        queue.pop();
                    }

                    string.setIsCorrect(false);
                }
        }
    }

    // Now we are going to print the results:
    for(auto & string : strings) {
        std::cout << "Line #" << ++counter << ": ";
        if(string.getIsCorrect()) {
            std::cout << "The result of the expression " << string << "is: " << string.getResult();
        } else {
            std::cout << "The expression " << string << "does not have the correct format to do the operation.";
        }
        std::cout << std::endl;
    }
}

// Do the exercise 4:
void exercise4(){

    // Declare the delimiters for the string:
    std::string delimiters = "+\\-*/%";

    // Aux float number to store the expressions:
    float number1 = 0.0f, number2 = 0.0f;

    // Declare counter for the number of lines:
    int counter = 0;

    // Extra flag to validate the result of 0:
    bool flag = false;

    // Aux string to store the operation:
    std::string operation;

    // Auxiliary strings vector to modify the queue:
    std::string aux_string, aux_string2;

    // Declare the strings vector to be analyzed:
    std::vector<StringStructure> strings;

    // Print the exercise:
    std::cout << "\nExercise 4: " << std::endl << std::endl;

    // Declare the file manager object:
    FileManager fileManager("../test_files/test_fourth_point.txt");

    // Grab each line of the file, separate each word by the selected delimiters:
    for(auto & line : fileManager.getFileContent()) {
        for(auto & word : line) {

            // Here we are using the StringStructure class to store the word and the delimiter:
            strings.push_back(StringStructure(word, delimiters));
        }
    }

    // We are going to use a queue to do the operations and validate the correct format:
    std::queue<std::string> queue;

    // Now we are going to do the operations:
    for(auto & string : strings) {

        if(string.getString().size() < 3) {
            string.setIsCorrect(false);
            continue;
        }
        for(auto & expresion : string.getString()) {

            // If the expresion is a number, we validate it and store it in the queue:
            if(string.validateRegularExpression(expresion, "[0-9]+(\\.[0-9]+)?")) {

                // If in the head of the queue is an operation, we store the number under the operation:
                if(string.getResult() == 0.0f && queue.size() > 0 && string.validateRegularExpression(queue.front(), "[" + delimiters + "]")) {
                    aux_string = queue.front();
                    queue.pop();
                    aux_string2 = queue.front();
                    queue.pop();
                    queue.push(aux_string);
                    queue.push(aux_string2);
                    queue.push(expresion);
                } else if(string.getResult() != 0.0f && queue.size() > 0 && string.validateRegularExpression(queue.front(), "[" + delimiters + "]")) {
                    aux_string = queue.front();
                    queue.pop();
                    queue.push(aux_string);
                    queue.push(expresion);
                } else {
                    queue.push(expresion);
                }

                // If the expresion is a delimiter, we validate it and apply the operation:
            } else if(string.validateRegularExpression(expresion, "[" + delimiters + "]")) {

                // Firs we need to verify that have at least one number in the queue:
                if(string.getResult() == 0.0f && queue.size() < 1) {
                    string.setIsCorrect(false);

                    // Restart the queue:
                    while(!queue.empty()) {
                        queue.pop();
                    }

                    // We break the loop:
                    break;
                } else if(string.getResult() != 0.0f && queue.size() < 2) {
                    queue.push(expresion);
                } else {

                    // Now we are going to put the operation in head of the queue, first save the number in the queue:
                    aux_string = queue.front();

                    // Remove the number from the queue:
                    queue.pop();

                    // Put the operation in the queue:
                    queue.push(expresion);

                    // Put the numbers in the queue:
                    queue.push(aux_string);
                }
            } else {
                string.setIsCorrect(false);

                // Restart the queue:
                while(!queue.empty()) {
                    queue.pop();
                }

                break;
            }

            // Now we are going to operate the numbers in the queue:
            if(string.validateRegularExpression(queue.front(), "[" + delimiters + "]") && queue.size() > 2) {

                // Grab the operation in the queue:
                operation = queue.front();

                // Remove the operation from the queue:
                queue.pop();

                // Grab the first number in the queue:
                number1 = std::stof(queue.front());

                // Remove the first number from the queue:
                queue.pop();

                // Grab the second number in the queue:
                number2 = std::stof(queue.front());

                // Remove the second number from the queue:
                queue.pop();

                // Do the operation and store the result in the queue:
                string.setResult(doOperation(operation, number1, number2));
            } else if(string.getResult() != 0.0f && queue.size() > 1) {

                // Grab the operation in the queue:
                operation = queue.front();

                // Remove the operation from the queue:
                queue.pop();

                // Grab the first number in the queue:
                number1 = string.getResult();

                // Grab the second number in the queue:
                number2 = std::stof(queue.front());

                // Remove the second number from the queue:
                queue.pop();

                // Do the operation and store the result in the queue:
                string.setResult(doOperation(operation, number1, number2));
            }
        }
    }

    // Now we are going to print the results:
    for(auto & string : strings) {
        std::cout << "Line #" << ++counter << ": ";
        if(string.getIsCorrect()) {
            std::cout << "The result of the expression " << string << "is: " << string.getResult();
        } else {
            std::cout << "The expression " << string << "does not have the correct format to do the operation.";
        }
        std::cout << std::endl;
    }
};