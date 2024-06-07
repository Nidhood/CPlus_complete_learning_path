#ifndef POINTERS_FUNCTIONS_DEFINITIONS_H
#define POINTERS_FUNCTIONS_DEFINITIONS_H

#include <stdio.h>

// Function #1: What happens when we pass a normal variable to a function?
void passByValue(int a);

// Function #2: What happens when we pass a pointer to a function?
void passByReference(int *a);

// Function #3: Keep persistence of more than one value.
void makeChangesInValues(int *a, char *c, float *d, double *e);

// Function #4: General pointer initialization.
void generalPointerInitialization(void *ptr, int type);

#endif
