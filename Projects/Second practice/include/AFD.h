//
// Created by Ivan Dario Orozco Ibanez on 6/02/24.
//

#ifndef SECOND_PRACTICE_AFD_H
#define SECOND_PRACTICE_AFD_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "FileManager.h"

// Declare the states:
typedef enum {
    STATE_INITIAL,
    STATE_LEAST_ONE_LETTER,
    STATE_LEAST_ONE_AT,
    STATE_LEAST_ONE_DOT,
    STATE_LEAST_LETTER_AFTER_DOT,
    STATE_FINAL
} States;

// Declare the AFD validation structure:
typedef struct {
    char* email;
    int index;
    States state;
} AFD;

// Declare functions:

// Set the AFD object (constructor):
AFD setAFD(const char* email);

// Set array of AFDs objects:
AFD* setAFDArray(Content *content, int size);

// Validate the email address using the AFD algorithm:
bool validate_email_address(AFD *afd);

// Make the loop, transition between states and validate the email address:
void validate_email(AFD *afd);

// Free the memory allocated by the AFD array:
void free_memory_afd(AFD *afd_array, int size);

#endif //SECOND_PRACTICE_AFD_H
