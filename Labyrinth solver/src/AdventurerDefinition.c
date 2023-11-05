#include "../include/AdventurerHeader.h"
#include <stdio.h> // input and output streams.

AdventurerT setAdventurer(const char *name, uchar FontColorAdventurer, uchar BgColorAdventurer, int FSM)
{

    // Set default settings for the new adventurer:
    AdventurerT newAdventurer = {
        .name = name,
        .color = {
            .fontColor = FontColorAdventurer,
            .backColor = BgColorAdventurer},
        .direction = {"Derecha", ">"}, // By default starts in right form.
        .currentLocation = {0, 0},
        .moveValidation = {0, 0, 0, 0}, // Default are all false.
        .currentState = STATE_INITIAL,
        .steps_counter = 0,
        .total_states = 0,
        .adventurer_index = 0,
        .adventurer_colitions = 0,
        .FSM = FSM};

    for (int i = 0; i < MAX_MEMORIZED_STEPS; i++)
    {
        newAdventurer.route[i].x = 0;
        newAdventurer.route[i].y = 0;
    }

    return newAdventurer;
}

void setAdventurerPosition(const char *position, AdventurerT *adventurer)
{
    if (strcmp(position, "Derecha") == 0)
    {
        adventurer->direction.description = "Derecha";
        adventurer->direction.symbol = ">";
    }
    else if (strcmp(position, "Izquierda") == 0)
    {
        adventurer->direction.description = "Izquierda";
        adventurer->direction.symbol = "<";
    }
    else if (strcmp(position, "Arriba") == 0)
    {
        adventurer->direction.description = "Arriba";
        adventurer->direction.symbol = "^";
    }
    else if (strcmp(position, "Abajo") == 0)
    {
        adventurer->direction.description = "Abajo";
        adventurer->direction.symbol = "V";
    }
    else
    {
        printf("Error: La posicion ingresada no es valida.\n");
    }
}
