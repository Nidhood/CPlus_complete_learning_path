//
// Created by Ivan Dario Orozco Ibanez on 6/02/24.
//

#include "AFD.h"
#include "Util.h"

//Define the function:

AFD setAFD(const char* email) {
    AFD afd;
    afd.email = strdup(email);
    afd.index = 0;
    afd.state = STATE_INITIAL;
    return afd;
}

AFD* setAFDArray(Content *content, int size) {
    AFD *afd_array = (AFD*)malloc(sizeof(AFD) * size);
    if (afd_array == NULL) {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        afd_array[i] = setAFD(content[i].line);
    }
    return afd_array;
}

bool validate_email_address(AFD *afd) {

    // Start the AFD algorithm:
    switch (afd->state) {

        case STATE_INITIAL:

            // Check if the first character is a letter:
            if (afd->email[afd->index] >= 'a' && afd->email[afd->index] <= 'z') {
                afd->state = STATE_LEAST_ONE_LETTER;
                return true;
            } else {
                return false;
            }

        case STATE_LEAST_ONE_LETTER:

            // Check if the character is a letter, anything else omits the validation:
            if (afd->email[afd->index] >= 'a' && afd->email[afd->index] <= 'z') {
                afd->state = STATE_LEAST_ONE_LETTER;
                return true;

            // Check if after the letter there is an '@':
            } else if (afd->email[afd->index] == '@') {
                afd->state = STATE_LEAST_ONE_AT;
                return true;

            // Else, the email is invalid:
            } else {
                return false;
            }

        case STATE_LEAST_ONE_AT:

            // Check if after the @ character there is a letter:
            if (afd->email[afd->index] >= 'a' && afd->email[afd->index] <= 'z') {
                afd->state = STATE_LEAST_ONE_AT;
                return true;

            // Check if after the @ character there is a dot:
            } else if (afd->email[afd->index] == '.') {
                afd->state = STATE_LEAST_ONE_DOT;
                return true;

            // Else, the email is invalid:
            } else {
                return false;
            }

        case STATE_LEAST_ONE_DOT:

            // Check if after the dot character there is a letter:
            if (afd->email[afd->index] >= 'a' && afd->email[afd->index] <= 'z') {
                afd->state = STATE_LEAST_LETTER_AFTER_DOT;
                return true;

            // Else, the email is invalid:
            } else {
                return false;
            }

        case STATE_LEAST_LETTER_AFTER_DOT:

            // Check if after the letter there is a letter:
            if (afd->email[afd->index] >= 'a' && afd->email[afd->index] <= 'z') {
                afd->state = STATE_LEAST_LETTER_AFTER_DOT;
                return true;

            // Check if after the letter there is a dot:
            } else if (afd->email[afd->index] == '.') {
                afd->state = STATE_LEAST_ONE_DOT;
                return true;

            // Check if there is nothing else after the letter (case 1 = end of the string, case 2 = end of the line) :
            } else if (afd->email[afd->index] == '\0' || afd->email[afd->index] == '\n') {
                afd->state = STATE_FINAL;
                return true;

            // Else, the email is invalid:
            } else {
                return false;
            }

        case STATE_FINAL:
            return false;

        default:
            return true;
    }
}

void validate_email(AFD *afd) {

    // Make the loop, transition between states and validate the email address:
    while (validate_email_address(afd)) {
        afd->index++;
    }

    // Print the result:
    if (afd->state == STATE_FINAL) {
        // BackgroundColor(GREEN_COLOR, NORMAL_COLOR);
        printf("The email address is valid: %s", afd->email);
        RstColor()
    } else {
        // BackgroundColor(RED_COLOR, NORMAL_COLOR);
        printf("The email address is invalid: %s", afd->email);
        RstColor()
    }
}

void free_memory_afd(AFD *afd_array, int size) {
    for (int i = 0; i < size; i++) {
        free(afd_array[i].email);
    }
    free(afd_array);
}