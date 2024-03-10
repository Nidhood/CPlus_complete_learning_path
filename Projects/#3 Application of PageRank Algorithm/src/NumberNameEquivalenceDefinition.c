#include "../include/NumberNameEquivalenceHeader.h"

// Create a NumberName structure from a file
NumberName *createNumberName(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Inicializar la estructura NumberName
    NumberName numberName;

    // Arreglos para almacenar los nombres y números de los papeles
    char paperNames[MAX_PAPER_NAME][MAX_LINE_LENGTH];
    int paperNumbers[MAX_PAPER_NAME];

    int paperCount = 0; // Contador para rastrear la cantidad de papeles procesados

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL && paperCount < MAX_PAPER_NAME) {
        char *delimiter = strchr(line, '>');
        if (delimiter != NULL) {
            *delimiter = '\0'; // Terminar la cadena en '>' para separar el nombre del papel
            strcpy(paperNames[paperCount], line); // Copiar el nombre del papel
            paperNumbers[paperCount] = atoi(delimiter + 1); // Asignar el número del papel
            paperCount++;
        }
    }

    fclose(file);



    // Copiar los datos de los papeles a la estructura NumberName
    for (int i = 0; i < paperCount; i++) {
        // Asignar memoria para un objeto Paper
        numberName.papers[i] = (Paper *)malloc(sizeof(Paper));
        if (numberName.papers[i] == NULL) {
            perror("Memory allocation failed");
            // Liberar la memoria asignada previamente
            for (int j = 0; j < i; j++) {
                free(numberName.papers[j]->paperName);
                free(numberName.papers[j]);
            }
            return NULL;
        }
        // Asignar memoria para el nombre del papel
        numberName.papers[i]->paperName = strdup(paperNames[i]);
        if (numberName.papers[i]->paperName == NULL) {
            perror("Memory allocation failed");
            // Liberar la memoria asignada previamente
            for (int j = 0; j <= i; j++) {
                free(numberName.papers[j]->paperName);
                free(numberName.papers[j]);
            }
            return NULL;
        }
        // Asignar el número del papel
        numberName.papers[i]->paperNumber = paperNumbers[i];
    }

    // Asignar la memoria necesaria para la estructura NumberName y copiar los datos
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