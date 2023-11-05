#ifndef INTELLI_MENUSHEADER_H
#define INTELLI_MENUSHEADER_H

#include <stdio.h>  // input and output streams.
#include <stdlib.h> // EXIT_SUCCESS return.
#include <string.h> // Allows operate with string types.
#include <unistd.h> // sleep() funcion.

#include "Util.h" // Colors library.

// Global variables:
#define MAX_MENU_OPTIONS 10

typedef struct OptionS OptionT;
struct OptionS
{
    int option_index;
    const char *optionDescription;
};

typedef struct MenuOptionsS MenuOptionsT;
struct MenuOptionsS
{
    const char *menuDescription;
    OptionT options[MAX_MENU_OPTIONS];
    int num_options;
};

// Display message.
void display_message(const char *message, uchar FontColor, uchar BgColor);

// Display menu options.
int display_menu(MenuOptionsT menu);

// Exit program.
void exitDisplay();

#endif // INTELLI_MENUSHEADER_H