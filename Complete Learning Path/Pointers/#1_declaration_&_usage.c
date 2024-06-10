#include "functions_definitions.h"

int main(void){

    // Always, we are working with normal variables assigned with values:
    int a = 10;

    // Let's see what happens when we pass a normal variable to a function:
    printf("Value of a before calling passByValue: %d\n", a);
    passByValue(a);
    printf("Value of a after calling passByValue: %d\n\n", a);

    // But what happens when we pass a pointer to a function?
    printf("Value of a before calling passByReference: %d\n", a);
    passByReference(&a);
    printf("Value of a after calling passByReference: %d\n", a);

    // But, the real question is: Why whe need to use pointers in functions, when we can use return values?
    // The answer is: Like python that we cant return multiple values, we can use pointers to return multiple values in C.
    // Let's see how it works:
    int a1 = 10;
    char c1 = 'x';
    float d1 = (float)3.5;
    double e1 = (double)4.5;
    printf("\nValues before calling makeChangesInValues: %d, %c, %.2f, %.2lf\n", a1, c1, d1, e1);
    makeChangesInValues(&a1, &c1, &d1, &e1);
    printf("Values after calling makeChangesInValues: %d, %c, %.2f, %.2lf\n", a1, c1, d1, e1);

    // Finally, we need to understand how the pointers works with arrays or structures in C.
    // Let's see how it works:
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;

    // An array is a collection of similar data types, like we already know. But, additionally and redundantly, an array is a pointer to the first element of the array.
    printf("\nArray values using pointer & address: %d - %p", *ptr, ptr);
    return 0;
}