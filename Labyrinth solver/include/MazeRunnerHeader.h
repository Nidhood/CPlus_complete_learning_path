#ifndef INTELLI_MAZERUNNERHEADER_H
#define INTELLI_MAZERUNNERHEADER_H

#include "AdventurerHeader.h"
#include "MapHeader.h"

// Steps to implement the code:

// 1. Define the behaviors of adventurers.
char adventurersMovement(AdventurerT *adventurer, MapT *map);

// 1.1. Define the behavior of the adventurer 1.
char FSM_BASIC(AdventurerT *adventurer, MapT *map);

// 1.2. Define the behavior of the adventurer 2.
char FSM_PROBABILITIES(AdventurerT *adventurer, MapT *map);

// 1.3. Define the behavior of the adventurer 2.
char FSM_RIGHT_HAND_LAY(AdventurerT *adventurer, MapT *map);

// 1.4. Define the behavior of the adventurer 2.
char FSM_RANDOM_DIRECTION(AdventurerT *adventurer, MapT *map);

// 2. With the new adventurers positions, update the map.
void updateMap(AdventurerT adventurer, MapT *map);

char validateClash(const char validateValue);

void cleanAdventurerRoute(MapT *map, AdventurerT adventurer);

#endif // INTELLI_MAZERUNNERHEADER_H


