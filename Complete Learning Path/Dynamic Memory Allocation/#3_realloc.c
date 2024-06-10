#include "dynamic_functions.h"
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// The last dynamic allocation function is "realloc", which is a function that changes the size of the memory block pointed to by ptr.
// The function may move the memory block to a new location (whose address is returned by the function).
// The content of the memory block is preserved up to the lesser of the new and old sizes, even if the block is moved to a new location.
// If the new size is larger, the value of the newly allocated portion is indeterminate.
// In case that ptr is NULL, the function behaves exactly as malloc, assigning a new block of size bytes and returning a pointer to the beginning of it.
// If the size is 0, the memory previously allocated in ptr is deallocated and a NULL pointer is returned.
// Let's see an example of how to use the "realloc" function:

int main(void){

    int *ptrArr = NULL;                                         // Not pointer to anywhere yet.
    int *tempPtr = NULL;                                        // Not pointer to anywhere yet.
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

    for(int i = 0; i < arrSize; i++)                            // Assigning values to the dynamic array.
        ptrArr[i] = i + 1;

    // Now, we are going to reallocate the memory block to a new size.
    arrSize = 5;                                                // New size of the dynamic array.
    tempPtr = (int *)realloc(ptrArr, arrSize * sizeof(int)); // We are returning a pointer to the first byte of the block, which creates a dynamic array of type of the data and multiplies it by the size of the array, making it dynamic.

    if(tempPtr == NULL) {                                        // If the reallocation fails, the function returns a null pointer.
        printf("Memory reallocation failed!\n");
        free(ptrArr); // Free the original block before exiting
        return 1;
    } else {
        printf("Memory reallocation successful!\n");
        ptrArr = tempPtr;
    }

    printf("\n");

    for(int i = 0; i < arrSize; i++)                            // Print all addresses of the dynamic array.
        printf("Address of the %d element: %p\n", i, &ptrArr[i]);
    printf("\n");

    for(int i = 3; i < arrSize; i++)                            // Assigning the new values to the dynamic array.
        ptrArr[i] = i * 2;

    for(int i = 0; i < arrSize; i++)                            // Print all values of the dynamic array.
        printf("Value of the %d element: %d\n", i, ptrArr[i]);
    printf("\n");

    free(ptrArr);                                           // Freeing the memory allocated by the "malloc" function.
    ptrArr = NULL;                                              // Setting the pointer to NULL, to avoid dangling pointers.
    return 0;
}