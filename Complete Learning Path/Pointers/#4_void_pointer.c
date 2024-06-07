#include <stdio.h>
#include "functions_definitions.h"

int main(){

    // Like we have seen in the previous snippets, we can use pointers to store the address of any variable.
    // Just creating a pointer with the specified type and assigning the address of the variable to it.
    // But what if we don't know the type of the variable?
    // We can use void pointers to store the address of any variable.
    // Let's see how it works:
    int a = 10;
    float b = (float)20.5;
    char c = 'A';
    void *p;

    // Assigning the address of the variable to the void pointer:
    p = &a;
    printf("Value of a using void pointer: %d\n", *(int *)p);

    p = &b;
    printf("Value of b using void pointer: %.2f\n", *(float *)p);

    p = &c;
    printf("Value of c using void pointer: %c\n", *(char *)p);

    // Using void pointers in functions, it is important to set the promotion to the correct type of pointer.

    // When is it useful to use void pointers?
    // When we don't know the type of the variable, we can use void pointers to store the address of the variable.
    // But, we need to know the type of the variable to dereference the void pointer.
    // Like in a general function that can accept any type of variable, we can use void pointers.
    // Let's see how it works:
    // generalPointerInitialization(&a, sizeof(a));
    // generalPointerInitialization(&b, sizeof(b));
    // generalPointerInitialization(&c, sizeof(c));
    return 0;
}