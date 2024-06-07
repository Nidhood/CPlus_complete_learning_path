#include <stdio.h>

int main(){

    // Referencing and dereferencing is a very important concept in C programming, especially when working with pointers.
    // Referencing: It is the process of storing the address of a variable in a pointer.
    // Dereferencing: It is the process of accessing the value of the variable using the pointer.
    // Let's see how referencing and dereferencing works:
    int a = 10;
    printf("Value of a: %d\n", a);
    printf("Address of a: %p\n", &a);
    printf("\n");

    // Referencing:
    int *p = &a;
    printf("Value of p: %p\n", p);
    printf("Address of p: %p\n", &p);
    printf("\n");

    // Dereferencing:
    printf("Value of a using pointer p: %d\n", *p);
    printf("\n");

    // Let's see what happens when we change the value of 'a' using the pointer p:
    *p = 20;
    printf("Value of a after changing using pointer p: %d\n", a);
    printf("\n");

    // Let's see what happens when we change the value of 'a' directly:
    a = 30;
    printf("Value of a after changing directly: %d\n", a);
    printf("\n");

    // Let's see what happens when we change the value of 'a' using the pointer p:
    *p = 40;
    printf("Value of a after changing using pointer p: %d\n", a);
    return 0;
}
