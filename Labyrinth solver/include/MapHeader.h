#ifndef INTELLI_MAPHEADER_H
#define INTELLI_MAPHEADER_H

#include <string.h>
#include <stdlib.h> // rand().
#include <time.h>   // time().
#include <math.h>   // sqrt().
#include "Util.h"   // Colors library.
#include "AdventurerHeader.h"
#include "MapHeader.h"

// Global variables:
#define MAX_SIZE 40
#define MAX_ADV_NAME_SIZE 20
#define MAX_ADVENTURERS 4

// Structs:
typedef struct AdventurerIndexS AdventurerIndexT;
struct AdventurerIndexS
{
    char adventurer[MAX_ADV_NAME_SIZE]; // Mutable.
};

typedef struct dataS dataT;
struct dataS
{
    char value;                                    // Mutable.
    AdventurerIndexT adventurers[MAX_ADVENTURERS]; // Mutable.
    int lastIndex;                                 // Mutable.
    float probability;                             // Mutable.
};

typedef struct MapS MapT;
struct MapS
{
    char *name;                       // Inmutable.
    char *description;                // Inmutable.
    char *path;                       // Inmutable.
    dataT matrix[MAX_SIZE][MAX_SIZE]; // Mutable.
};

// Steps to implement the code:

// 1. Select map (based on the files maps inside the folder 'maps') and get data.
int getMap(MapT *map, AdventurerT adventurers[MAX_ADVENTURERS], int map_option, int map_probability_option, int *counter_adventures);
float calculateDistanceToWall(int x, int y, int max_size);
void updateProbabilities(MapT *map, int x, int y);

// 2. Draw map.
void drawMap(MapT map, AdventurerT adventurers[MAX_ADVENTURERS], uchar FontColorWall, uchar BgColorWall, uchar FontColorGoal, uchar BgColorGoal);
void drawProbabilitiesMap(MapT map, AdventurerT adventurers[MAX_ADVENTURERS], uchar FontColorWall, uchar BgColorWall, uchar FontColorGoal, uchar BgColorGoal);

// 3. Draw win map.
void drawWinMap(MapT map, AdventurerT adventurers[MAX_ADVENTURERS], uchar FontColorWall, uchar BgColorWall, uchar FontColorGoal, uchar BgColorGoal);

// 4. Validate if there is any adventurers in the position.
char hasAdventurer(const AdventurerIndexT adventurers[MAX_ADVENTURERS]);

// Constructor
MapT createMap(const char *name, const char *description, const char *path);

#endif