#include "functions_definitions.h"

// Function #1: What happens when we pass a normal variable to a function?
void passByValue(int a){
    printf("Value of a inside the function: %d\n", a);
    a = 20;
    printf("Value of a inside the function after changing: %d\n", a);
}

// Function #2: What happens when we pass a pointer to a function?
void passByReference(int *a){
    printf("Value of a inside the function: %d\n", *a);
    *a = 20;
    printf("Value of a inside the function after changing: %d\n", *a);
}

// Function #3: Keep persistence of more than one value.
void makeChangesInValues(int *a, char *c, float *d, double *e){
    *a = 20;
    *c = 'A';
    *d = (float)10.5;
    *e = (double)230.5;
}

// Function #4: General pointer initialization.
void generalPointerInitialization(void *ptr, int type){
    if(type == sizeof(int)){
        printf("The pointer is pointing to an integer variable\n");
    } else if(type == sizeof(float)){
        printf("The pointer is pointing to a float variable\n");
    } else if(type == sizeof(char)){
        printf("The pointer is pointing to a char variable\n");
    } else if(type == sizeof(double)){
        printf("The pointer is pointing to a double variable\n");
    } else {
        printf("Invalid type\n");
    }
}