#include "dynamic_functions.h"
#include <stdlib.h>

// Starting with the first dynamic allocation function, we have the "malloc" function.
// "malloc" is a function that allocates a block of memory (sequence of bytes) of a specified size and returns a pointer to the first byte of the block.
// If the allocation fails, the function returns a null pointer.
// Let's see an example of how to use the "malloc" function:

int main(void) {

    int *ptrArr;                                                // Not pointer to anywhere yet.
    int arrSize = 3;                                            // Specifying the size of the dynamic array.
    ptrArr = (int *)malloc(arrSize * sizeof(int));         // We are returning a pointer to the first byte of the block, which creates a dynamic array of type of the data and multiplies it by the size of the array, making it dynamic.
    if(ptrArr == NULL) {                                        // If the allocation fails, the function returns a null pointer.
        printf("Memory allocation failed!\n");
        return 1;
    } else
        printf("Memory allocation successful!\n");
    printf("\n");

    for(int i = 0; i < arrSize; i++)                            // Print all addresses of the dynamic array.
        printf("Address of the %d element: %p\n", i, &ptrArr[i]);
    printf("\n");

    for(int i = 0; i < arrSize; i++)                            // Print all values of the dynamic array (which are initialized with garbage values).
        printf("Value of the %d element: %d\n", i, ptrArr[i]);
    printf("\n");

    for(int i = 0; i < arrSize; i++)                            // Assigning values to the dynamic array.
        ptrArr[i] = i + 1;

    for(int i = 0; i < arrSize; i++)                            // Print all values of the dynamic array.
        printf("Value of the %d element: %d\n", i, ptrArr[i]);

    free(ptrArr);                                           // Freeing the memory allocated by the "malloc" function.

    // What is a dangling pointer?
    // -> A dangling pointer is a pointer that points to a memory location that has been deallocated or freed, which can cause a program to crash or behave unexpectedly.
    ptrArr = NULL;                                              // Setting the pointer to NULL, to avoid dangling pointers.
    return 0;
}
