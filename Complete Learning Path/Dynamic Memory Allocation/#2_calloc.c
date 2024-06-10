#include "dynamic_functions.h"
#include <stdlib.h>

// Now, the second dynamic function is "calloc", which is a function that allocates memory for an array of num objects
// of size bytes each and returns a pointer to the allocated memory. The memory is set to zero. If num or size is 0,
// then calloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().
// But, what is the difference between "malloc" and "calloc"?
// -> The difference is that "malloc" does not set the memory to zero, while "calloc" does.
// More certainty, "calloc" initializes all bytes in the allocated memory to zero, while "malloc" leaves the memory uninitialized with some garbage values.
// Let's see an example of how to use the "calloc" function:

int main(void) {

    int *ptrArr;                                                      // Not pointer to anywhere yet.
    int arrSize = 3;                                                  // Specifying the size of the dynamic array.
    ptrArr = (int *)calloc(arrSize, sizeof(int));        // We are returning a pointer to the first byte of the block, which creates a dynamic array of type of the data and multiplies it by the size of the array, making it dynamic.

    if(ptrArr == NULL) {                                    // If the allocation fails, the function returns a null pointer.
        printf("Memory allocation failed!\n");
        return 1;
    } else
        printf("Memory allocation successful!\n");
    printf("\n");

    for(int i = 0; i < arrSize; i++)                              // Print all addresses of the dynamic array.
        printf("Address of the %d element: %p\n", i, &ptrArr[i]);
    printf("\n");

    for(int i = 0; i < arrSize; i++)                              // Print all values of the dynamic array (which are all zero).
        printf("Value of the %d element: %d\n", i, ptrArr[i]);
    printf("\n");

    for(int i = 0; i < arrSize; i++)                              // Assigning values to the dynamic array.
        ptrArr[i] = i + 1;

    for(int i = 0; i < arrSize; i++)                              // Print all values of the dynamic array.
        printf("Value of the %d element: %d\n", i, ptrArr[i]);

    free(ptrArr);                                             // Freeing the memory allocated by the "calloc" function.
    return 0;
}