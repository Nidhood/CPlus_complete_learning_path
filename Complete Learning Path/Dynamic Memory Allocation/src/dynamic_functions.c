#include "dynamic_functions.h"

// Function #1: Swap two arrays using pointers (which reduce de complexity to O(1)).
void swapArraysUsingPointers(void **arr1, void **arr2){
    void *temp = *arr1;
    *arr1 = *arr2;
    *arr2 = temp;
}