#ifndef PROYECTO_NUMBERNAMEEQUIVALENCEHEADER_H
#define PROYECTO_NUMBERNAMEEQUIVALENCEHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAPER_NAME 3237
#define MAX_LINE_LENGTH 1000

// Data structures:
typedef struct {
    char *paperName;
    int paperNumber;
} Paper;

typedef struct {
    Paper *papers[MAX_PAPER_NAME];
    char *fileName;
} NumberName;

// Function prototypes:
NumberName *createNumberName(const char *fileName);
void freeNumberName(NumberName *numberName);

#endif