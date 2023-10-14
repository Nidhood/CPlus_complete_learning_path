#ifndef INTELLI_ADVENTURERHEADER_H
#define INTELLI_ADVENTURERHEADER_H

// Global variables:
#define MAX_MEMORIZED_STEPS 1444

#include "Util.h"
#include "string.h"

// Enum:

// Define the states for the finite state machine using enum data type.

// An enum in C is an enumeration that provides a set of symbolic names (labels)
// for representing constant integer values. It's a way of assigning more readable
// names to numeric values, making the code clearer and less error-prone.
// Source : https://cplusplus.com/doc/tutorial/other_data_types/

typedef enum StateS StateT;
enum StateS
{
    STATE_INITIAL,
    STATE_MOVE_FORWARD,
    STATE_TURN_RIGHT,
    STATE_TURN_LEFT,
    STATE_MOVE_BACKWARDS,
    STATE_CLASH,
    STATE_REAPPEAR,
    STATE_CHECK_PROBABILITIES,
    STATE_FINAL

    // Here in the enum State is used to define the possible states of
    // a finite state machine. In this case, the states are :

    // 1. STATE_INITIAL.
    // 2. STATE_CHECK_FORWARD.
    // 3. STATE_MOVE_FORWARD.
    // 4. STATE_TURN_RIGHT.
    // 5. STATE_COUNT.

    // By assigning these names, we can use them instead of direct numeric
    // values when working with variables of type State. For instance:

    // State currentState = STATE_INITIAL;

    // Instead of:

    // int currentState = 0; // If STATE_INITIAL is at position 0

    // This makes the code more readable and less error-prone when dealing
    // with different states or constant values in your program.
};

// Structs:
typedef struct PositionS PositionT;
struct PositionS
{
    const char *description; // Inmutable.
    const char *symbol;      // Inmutable.
};

typedef struct LocationS LocationT;
struct LocationS
{
    int x; // Mutable.
    int y; // Mutable.
};

typedef struct ColorS ColorT;
struct ColorS
{
    uchar fontColor; // Inmutable.
    uchar backColor; // Inmutable.
};

typedef struct MoveValidationS MoveValidationT;
struct MoveValidationS
{
    char up;
    char down;
    char right;
    char left;
};

typedef struct AdventurerS AdventurerT;
struct AdventurerS
{
    const char *name;                     // Inmutable.
    ColorT const color;                   // Inmutable.
    PositionT direction;                  // Mutable.
    LocationT currentLocation;            // Mutable.
    LocationT route[MAX_MEMORIZED_STEPS]; // Number of steps that the adventurer can remember
    MoveValidationT moveValidation;       // Mutable.
    StateT currentState;                  // Mutable.
    int steps_counter;                    // Counter of steps (just forward).
    int total_states;                     // Counter of states (ALL).
    int adventurer_index;                 // Index of adventurer in the array of adventurers.
    int adventurer_colitions;             // Number of colitions with another aventurer (MAX 3).
    int FSM;                              // Type of intelligent algorithm to use (0 = FSM (basic right hand), 1 = FMS (Probability), 2 = FMS (Analitics) , 2 = FMS (Analitics & Probability)).
};

// Steps to implement the code:

// 1. Create an adventurer.
AdventurerT setAdventurer(const char *name, uchar FontColorAdventurer, uchar BgColorAdventurer, int FSM);

void setAdventurerPosition(const char *position, AdventurerT *adventurer);
#endif