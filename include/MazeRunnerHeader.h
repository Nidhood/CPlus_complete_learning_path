//
// Created by Ivan Dario Orozco Ibañez on 10/10/23.
//

#ifndef INTELLI_MAZERUNNERHEADER_H
#define INTELLI_MAZERUNNERHEADER_H

#include "AdventurerHeader.h"
#include "MapHeader.h"

// Steps to implement the code:

// 1. Define the behaviors of adventurers.
char adventurersMovement(AdventurerT *adventurer, MapT *map);

// 2. With the new adventurers positions, update the map.
void updateMap(AdventurerT adventurer, MapT *map);

char validateClash(const char validateValue);

void cleanAdventurerRoute(MapT *map, AdventurerT adventurer);

#endif // INTELLI_MAZERUNNERHEADER_H
