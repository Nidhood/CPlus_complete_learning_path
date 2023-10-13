#include "../include/MapHeader.h"
#include <stdio.h> // input and output streams.

int roads(MapT map)
{
    int counter = 0;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (map.matrix[i][j].value == ' ')
            {
                counter++;
            }
        }
    }
    return counter;
}

char hasAdventurer(const AdventurerIndexT adventurers[MAX_ADVENTURERS])
{
    for (int i = 0; i < MAX_ADVENTURERS; ++i)
    {
        if (adventurers[i].adventurer[0] != '\0')
        {
            // The adventurer's name at position i is not empty
            return 1;
        }
    }
    // No adventurer found
    return 0;
}

int getMap(MapT *map, AdventurerT adventurers[MAX_ADVENTURERS], int map_option)
{
    int boxes, counter_adventurers = 0;
    FILE *file = fopen(map->path, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_SIZE; ++j)
        {
            char c;

            // Skip characters until an opening single quote is found
            while (fscanf(file, "%c", &c) == 1 && c != '\'')
                ;

            // Read the character inside the single quotes
            if (fscanf(file, "%c", &c) == 1)
            {
                if (c == '>' || c == '<' || c == 'V' || c == '^')
                {
                    map->matrix[i][j].value = c;
                    strcpy(map->matrix[i][j].adventurers[counter_adventurers].adventurer, adventurers[counter_adventurers].name);
                    map->matrix[i][j].probability = 1.0f / MAX_SIZE;
                    adventurers[counter_adventurers].currentLocation.x = i;
                    adventurers[counter_adventurers].currentLocation.y = j;
                    adventurers[counter_adventurers].adventurer_index = counter_adventurers;
                    switch (c)
                    {
                    case '>':
                        setAdventurerPosition("Derecha", &adventurers[counter_adventurers]);
                        break;
                    case '<':
                        setAdventurerPosition("Izquierda", &adventurers[counter_adventurers]);
                        break;
                    case 'V':
                        setAdventurerPosition("Abajo", &adventurers[counter_adventurers]);
                        break;
                    case '^':
                        setAdventurerPosition("Arriba", &adventurers[counter_adventurers]);
                        break;
                    default:
                        break;
                    }

                    counter_adventurers++;
                }
                else
                {
                    map->matrix[i][j].value = c;

                    // To not mix the index position of the existence of the adventurer we use -1.
                    map->matrix[i][j].lastIndex = -1;
                }
            }
            else
            {
                // Handle the case where there is no character inside the single quotes
                perror("Error reading file");
                fclose(file);
                return 0;
            }

            // Skip characters until a closing single quote is found
            while (fscanf(file, "%c", &c) == 1 && c != '\'')
                ;
        }
    }
    fclose(file);

    // Probability in each box:
    boxes = roads(*map);

    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (map->matrix[i][j].value == ' ')
            {
                map->matrix[i][j].probability = 1.0f / (float)boxes;
            }
        }
    }
    return map_option;
}

void clearScreen()
{
    printf("\033[H\033[J"); // ANSI code to clear screen
    fflush(stdout);         // Asegurarse de que la salida se ha vaciado
}

// Draw map:
void drawMap(MapT map, AdventurerT adventurers[MAX_ADVENTURERS], uchar FontColorWall, uchar BgColorWall, uchar FontColorGoal, uchar BgColorGoal)
{
    Cls();

    // Array to track whether an adventurer has been found at each position
    char adventurer_found[MAX_SIZE][MAX_SIZE] = {0};

    // Index of the last adventurer found.
    for (int y = MAX_SIZE - 1; y >= 0; --y)
    {
        printf("\t\t\t");
        for (int x = 0; x < MAX_SIZE; ++x)
        {
            if (x == 0 && y == 0)
            {
                BackgroundColor(FontColorWall, BgColorWall);
                printf("%c  ", map.matrix[x][y].value);
                RstColor();
            }
            else if (map.matrix[x][y].value == 'O')
            {
                BackgroundColor(FontColorGoal, BgColorGoal);
                printf("%c  ", map.matrix[x][y].value);
                RstColor();
            }
            else if (map.matrix[x][y].value == '*')
            {
                BackgroundColor(FontColorWall, BgColorWall);
                printf("%c  ", map.matrix[x][y].value);
                RstColor();
            }
            else if (hasAdventurer(map.matrix[x][y].adventurers))
            {
                for (int k = 0; k < MAX_ADVENTURERS; ++k)
                {
                    for (int l = 0; l < MAX_ADVENTURERS; ++l)
                    {
                        if (!adventurer_found[x][y] && strcmp(map.matrix[x][y].adventurers[l].adventurer, adventurers[k].name) == 0)
                        {
                            BackgroundColor(adventurers[map.matrix[x][y].lastIndex].color.fontColor, adventurers[map.matrix[x][y].lastIndex].color.backColor);
                            printf("%c  ", map.matrix[x][y].value);
                            RstColor();

                            // Set the flag to true.
                            adventurer_found[x][y] = 1;
                            break;
                        }
                    }
                }
            }
            else
            {
                printf("%c  ", map.matrix[x][y].value);
            }
        }
        printf("\n");
    }
    for (int i = 0; i < MAX_ADVENTURERS; ++i)
    {
        BackgroundColor(adventurers[i].color.backColor, adventurers[i].color.fontColor);
        printf("\nCantidad de pasos realizados por el aventurero '%s': ", adventurers[i].name);
        BackgroundColor(adventurers[i].color.fontColor, adventurers[i].color.backColor);
        printf(" %d\n", adventurers[i].steps_counter);
        BackgroundColor(adventurers[i].color.backColor, adventurers[i].color.fontColor);
        printf("\nCantidad de estados por los cuales paso el aventurero '%s': ", adventurers[i].name);
        BackgroundColor(adventurers[i].color.fontColor, adventurers[i].color.backColor);
        printf(" %d\n", adventurers[i].total_states);
        printf("\n");
    }
}

// Draw win map:
void drawWinMap(MapT map, AdventurerT adventurers[MAX_ADVENTURERS], uchar FontColorWall, uchar BgColorWall, uchar FontColorGoal, uchar BgColorGoal)
{
    char adventurer_found[MAX_SIZE][MAX_SIZE] = {0};
    for (int y = MAX_SIZE - 1; y >= 0; --y)
    {
        printf("\t\t\t");
        for (int x = 0; x < MAX_SIZE; ++x)
        {
            if (x == 0 && y == 0)
            {
                BackgroundColor(FontColorWall, BgColorWall);
                printf("%c  ", map.matrix[x][y].value);
                RstColor();
            }
            else if (map.matrix[x][y].value == 'O')
            {
                BackgroundColor(FontColorGoal, BgColorGoal);
                printf("%c  ", map.matrix[x][y].value);
                RstColor();
            }
            else if (map.matrix[x][y].value == '*')
            {
                BackgroundColor(FontColorWall, BgColorWall);
                printf("%c  ", map.matrix[x][y].value);
                RstColor();
            }
            else if (hasAdventurer(map.matrix[x][y].adventurers))
            {
                for (int k = 0; k < MAX_ADVENTURERS; ++k)
                {
                    for (int l = 0; l < MAX_ADVENTURERS; ++l)
                    {
                        if (!adventurer_found[x][y] && strcmp(map.matrix[x][y].adventurers[l].adventurer, adventurers[k].name) == 0)
                        {
                            BackgroundColor(adventurers[k].color.fontColor, adventurers[k].color.backColor);
                            printf("%c  ", map.matrix[x][y].value);
                            RstColor();
                            adventurer_found[x][y] = 1; // Set the flag to true
                            break;
                        }
                    }
                }
            }
            else
            {
                printf("%c  ", map.matrix[x][y].value);
            }
        }
        printf("\n");
    }
    for (int i = 0; i < MAX_ADVENTURERS; ++i)
    {
        BackgroundColor(GREEN_COLOR, BLACK_COLOR);
        printf("\nCantidad de pasos realizados por el aventurero '%s': ", adventurers[i].name);
        BackgroundColor(adventurers[i].color.fontColor, adventurers[i].color.backColor);
        printf("%d\n", adventurers[i].steps_counter);
        BackgroundColor(GREEN_COLOR, BLACK_COLOR);
        printf("\nCantidad de estados por los cuales paso el aventurero '%s': ", adventurers[i].name);
        BackgroundColor(adventurers[i].color.fontColor, adventurers[i].color.backColor);
        printf("%d\n", adventurers[i].total_states);
        printf("\n");
        RstColor();
    }
    Pause();
}

// Constructor
MapT createMap(const char *name, const char *description, const char *path)
{
    MapT newMap;

    // Immutable
    newMap.name = strdup(name);
    newMap.description = strdup(description);
    newMap.path = strdup(path);

    // Mutable
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_SIZE; ++j)
        {
            newMap.matrix[i][j].value = '\0';
        }
    }
    return newMap;
}