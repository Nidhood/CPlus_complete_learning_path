#include <stdio.h>
#include <stdint.h>

int main() {

    // Now, we need to understand how pointer arithmetic works in C programming.
    // Pointer arithmetic is the process of adding or subtracting an integer value to a pointer.
    // Returning with the array example, let's see how pointer arithmetic works using different data types:
    uint8_t arrChar[5] = {1, 2, 3, 4, 5};
    uint16_t arrShort[5] = {1, 2, 3, 4, 5};
    uint32_t arrLong[5] = {1, 2, 3, 4, 5};
    uint64_t arrLongLong[5] = {1, 2, 3, 4, 5};

    // Let's see how pointer arithmetic works with char data type:
    uint8_t *ptrChar = arrChar;
    for (int i = 0; i < 5; i++) {
        printf("Value of arrChar[%d]: %d - Address of arrChar[%d]: %p\n", i, *(ptrChar + i), i, ptrChar + i);
    }
    printf("\n");

    // Let's see how pointer arithmetic works with short data type:
    uint16_t *ptrShort = arrShort;
    for (int i = 0; i < 5; i++) {
        printf("Value of arrShort[%d]: %d - Address of arrShort[%d]: %p\n", i, *(ptrShort + i), i, ptrShort + i);
    }
    printf("\n");

    // Let's see how pointer arithmetic works with long data type:
    uint32_t *ptrLong = arrLong;
    for (int i = 0; i < 5; i++) {
        printf("Value of arrLong[%d]: %d - Address of arrLong[%d]: %p\n", i, *(ptrLong + i), i, ptrLong + i);
    }
    printf("\n");

    // Let's see how pointer arithmetic works with long long data type:
    uint64_t *ptrLongLong = arrLongLong;
    for (int i = 0; i < 5; i++) {
        printf("Value of arrLongLong[%d]: %lu - Address of arrLongLong[%d]: %p\n", i, *(ptrLongLong + i), i,
               ptrLongLong + i);
    }
    printf("\n");

    // In brief, pointer arithmetic is the process of adding or subtracting an integer value to a pointer that represents the value of the data type.

    // A very important method to understand how pointer arithmetic works is to use the sizeof() function.
    // Let's see how it works:
    uint8_t *ptr = arrChar;
    for (int i = 0; i < 5; i++) {
        printf("Value of arrChar[%d]: %d - Address of arrChar[%d]: %p\n", i, *(ptr + i), i, ptr + i);
        printf("Size of arrChar[%d]: %lu\n", i, sizeof(*(ptr + i)));
    }
    printf("\n");
    printf("Size of arrChar: %lu\n", sizeof(arrChar));

    // Now, let's see what happens when we use the sizeof() function with a pointer:
    printf("\n");
    // Although the pointer is a variable, the sizeof() function returns the size of the pointer, not the size of the data type, which is not very important.
    // The size of the pointer is the same for all data types, which is 8 bytes (64 bits) in a 64-bit system. Or 4 bytes (32 bits) in a 32-bit system.
    printf("Size of ptr: %lu\n", sizeof(ptr));

    // In brief, the sizeof() function returns the size of the data type in bytes.
    return 0;
}