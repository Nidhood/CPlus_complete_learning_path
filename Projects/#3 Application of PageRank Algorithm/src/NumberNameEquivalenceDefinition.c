#include "../include/NumberNameEquivalenceHeader.h"

// Create a NumberName structure from a file:
NumberName *createNumberName(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Initialize the structure NumberName:
    NumberName numberName;

    // Arrays to store the names and numbers of the papers:
    char paperNames[MAX_PAPER_NAME][MAX_LINE_LENGTH];
    int paperNumbers[MAX_PAPER_NAME];

    // Counter to track the amount of papers processed:
    int paperCount = 0;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL && paperCount < MAX_PAPER_NAME) {
        char *delimiter = strchr(line, ',');
        if (delimiter != NULL) {

            // Split the line into the paper name and the paper number:
            *delimiter = '\0';

            // Copy the paper name:
            strcpy(paperNames[paperCount], line);

            // Assign the paper number:
            paperNumbers[paperCount] = atoi(delimiter + 1);
            paperCount++;
        }
    }
    fclose(file);

    // Copy all data to the structure NumberName:
    for (int i = 0; i < paperCount; i++) {

        // Assign the memory for a Paper object:
        numberName.papers[i] = (Paper *)malloc(sizeof(Paper));
        if (numberName.papers[i] == NULL) {
            perror("Memory allocation failed");

            // Free the memory allocated previously:
            for (int j = 0; j < i; j++) {
                free(numberName.papers[j]->paperName);
                free(numberName.papers[j]);
            }
            return NULL;
        }

        // Assign the memory for the paper name:
        numberName.papers[i]->paperName = strdup(paperNames[i]);
        if (numberName.papers[i]->paperName == NULL) {
            perror("Memory allocation failed");

            // Free the memory allocated previously:
            for (int j = 0; j <= i; j++) {
                free(numberName.papers[j]->paperName);
                free(numberName.papers[j]);
            }
            return NULL;
        }

        // Assign the number of the paper:
        numberName.papers[i]->paperNumber = paperNumbers[i];
    }

    // Assign the memory for the file name:
    static NumberName result; // Estructura estática
    memcpy(&result, &numberName, sizeof(NumberName));

    return &result;
}

void freeNumberName(NumberName *numberName) {
    for (int i = 0; i < MAX_PAPER_NAME; i++) {
        free(numberName->papers[i]->paperName);
        free(numberName->papers[i]);
    }
    free(numberName->fileName);
    free(numberName);
}