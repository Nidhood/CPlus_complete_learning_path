#include "../include/MapHeader.h"
#include <stdio.h> // input and output streams.
#include <ctype.h> // toUpper().

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

void updateProbabilities(MapT *map, int x, int y)
{

    // Reduce the probability of the chosen path to zero
    map->matrix[x][y].probability = 0.0f;

    // Update the probabilities of the remaining paths
    float totalProbability = 0.0f;

    // Calculate the new total probability
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (map->matrix[i][j].value == ' ')
            {
                totalProbability += map->matrix[i][j].probability;
            }
        }
    }

    // Ensure totalProbability is not zero before normalization
    if (totalProbability > 0.0f)
    {
        // Normalize the probabilities
        for (int i = 0; i < MAX_SIZE; i++)
        {
            for (int j = 0; j < MAX_SIZE; j++)
            {
                if (map->matrix[i][j].value == ' ')
                {
                    map->matrix[i][j].probability = 1 / totalProbability;
                }
            }
        }
    }
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

// Calculate the distance from the point (x, y) to the wall of the square matrix
float calculateDistanceToWall(int x, int y, int max_size)
{
    // Calculate the distance to the wall in each direction
    float distanceToTop = y;
    float distanceToBottom = max_size - 1 - y;
    float distanceToLeft = x;
    float distanceToRight = max_size - 1 - x;

    // Find the minimum distance to the wall in any direction
    float minDistance = distanceToTop;

    if (distanceToBottom < minDistance)
    {
        minDistance = distanceToBottom;
    }

    if (distanceToLeft < minDistance)
    {
        minDistance = distanceToLeft;
    }

    if (distanceToRight < minDistance)
    {
        minDistance = distanceToRight;
    }

    return minDistance;
}

float calculateDistanceToCenter(int x, int y, int max_size)
{
    // Calculate the coordinates of the center
    float centerX = (float)max_size / 2.0f;
    float centerY = (float)max_size / 2.0f;

    // Calculate the Euclidean distance
    float distance = sqrt(pow((float)x - centerX, 2) + pow((float)y - centerY, 2));
    return distance;
}

int getMap(MapT *map, AdventurerT adventurers[MAX_ADVENTURERS], int map_option, int map_probability_option, int *counter_adventures) // 0 : extremes, 1 : center.
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
                if (toupper(c) == '>' || toupper(c) == '<' || toupper(c) == 'V' || toupper(c) == '^')
                {
                    map->matrix[i][j].value = c;
                    strcpy(map->matrix[i][j].adventurers[counter_adventurers].adventurer, adventurers[counter_adventurers].name);
                    map->matrix[i][j].probability = 1.0f / MAX_SIZE;
                    map->matrix[i][j].lastIndex = adventurers[counter_adventurers].adventurer_index;
                    adventurers[counter_adventurers].currentLocation.x = i;
                    adventurers[counter_adventurers].currentLocation.y = j;
                    adventurers[counter_adventurers].adventurer_index = counter_adventurers;
                    switch (toupper(c))
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
                    map->matrix[i][j].value = toupper(c);

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

    // Obtain de total adveturers found in the file:
    *counter_adventures = counter_adventurers;

    // Probability in each box:
    boxes = roads(*map);

    if (map_probability_option == 0)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            for (int j = 0; j < MAX_SIZE; j++)
            {
                if (map->matrix[i][j].value == ' ')
                {
                    int paths = 0;                 // Counter for possible paths
                    float totalProbability = 0.0f; // Total probability to distribute among paths

                    // Check if there is a path above
                    if (i > 0 && map->matrix[i - 1][j].value == ' ')
                    {
                        paths++;
                    }

                    // Check if there is a path below
                    if (i < MAX_SIZE - 1 && map->matrix[i + 1][j].value == ' ')
                    {
                        paths++;
                    }

                    // Check if there is a path to the left
                    if (j > 0 && map->matrix[i][j - 1].value == ' ')
                    {
                        paths++;
                    }

                    // Check if there is a path to the right
                    if (j < MAX_SIZE - 1 && map->matrix[i][j + 1].value == ' ')
                    {
                        paths++;
                    }

                    // Assign probability based on the number of possible paths
                    if (paths == 3)
                    {
                        totalProbability = 1.0f / 3.0f;
                    }
                    else if (paths == 4)
                    {
                        totalProbability = 1.0f / 4.0f;
                    }

                    // Calculate distance to the wall and add probability based on it
                    float distanceToWall = calculateDistanceToWall(i, j, MAX_SIZE);
                    //  float additionalProbability = 1.0f / (40 + 40) - distanceToWall / (40 + 40);
                    totalProbability += distanceToWall;

                    // Assign probability to each path
                    if (i > 0 && map->matrix[i - 1][j].value == ' ')
                    {
                        map->matrix[i - 1][j].probability = totalProbability;
                    }

                    if (i < MAX_SIZE - 1 && map->matrix[i + 1][j].value == ' ')
                    {
                        map->matrix[i + 1][j].probability = totalProbability;
                    }

                    if (j > 0 && map->matrix[i][j - 1].value == ' ')
                    {
                        map->matrix[i][j - 1].probability = totalProbability;
                    }

                    if (j < MAX_SIZE - 1 && map->matrix[i][j + 1].value == ' ')
                    {
                        map->matrix[i][j + 1].probability = totalProbability;
                    }
                }
            }
        }
    }
    else if (map_probability_option == 1)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            for (int j = 0; j < MAX_SIZE; j++)
            {
                if (map->matrix[i][j].value == ' ')
                {
                    int paths = 0;                 // Counter for possible paths
                    float totalProbability = 0.0f; // Total probability to distribute among paths

                    // Check if there is a path above
                    if (i > 0 && map->matrix[i - 1][j].value == ' ')
                    {
                        paths++;
                    }

                    // Check if there is a path below
                    if (i < MAX_SIZE - 1 && map->matrix[i + 1][j].value == ' ')
                    {
                        paths++;
                    }

                    // Check if there is a path to the left
                    if (j > 0 && map->matrix[i][j - 1].value == ' ')
                    {
                        paths++;
                    }

                    // Check if there is a path to the right
                    if (j < MAX_SIZE - 1 && map->matrix[i][j + 1].value == ' ')
                    {
                        paths++;
                    }

                    // Assign probability based on the number of possible paths
                    if (paths == 3)
                    {
                        totalProbability = 1.0f / 3.0f;
                    }
                    else if (paths == 4)
                    {
                        totalProbability = 1.0f / 4.0f;
                    }

                    // Calculate distance to the center and add probability based on it
                    float distanceToCenter = calculateDistanceToCenter(i, j, MAX_SIZE);
                    // float additionalProbability = 1.0f / (40 + 40) - distanceToCenter / (40 + 40);
                    totalProbability += distanceToCenter;

                    // Assign probability to each path
                    if (i > 0 && map->matrix[i - 1][j].value == ' ')
                    {
                        map->matrix[i - 1][j].probability = totalProbability;
                    }

                    if (i < MAX_SIZE - 1 && map->matrix[i + 1][j].value == ' ')
                    {
                        map->matrix[i + 1][j].probability = totalProbability;
                    }

                    if (j > 0 && map->matrix[i][j - 1].value == ' ')
                    {
                        map->matrix[i][j - 1].probability = totalProbability;
                    }

                    if (j < MAX_SIZE - 1 && map->matrix[i][j + 1].value == ' ')
                    {
                        map->matrix[i][j + 1].probability = totalProbability;
                    }
                }
            }
        }
    }

    return map_option;
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
    fflush(stdout);
}

// Draw map:
void drawProbabilitiesMap(MapT map, AdventurerT adventurers[MAX_ADVENTURERS], uchar FontColorWall, uchar BgColorWall, uchar FontColorGoal, uchar BgColorGoal)
{
    Cls();

    // Index of the last adventurer found.
    for (int y = MAX_SIZE - 1; y >= 0; --y)
    {
        printf("\t\t\t");
        for (int x = 0; x < MAX_SIZE; ++x)
        {
            printf("%.4f  ", map.matrix[x][y].probability);
        }
        printf("\n");
    }
    fflush(stdout);
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
        BackgroundColor(adventurers[i].color.backColor, adventurers[i].color.fontColor);
        printf("\nCantidad de pasos realizados por el aventurero '%s': ", adventurers[i].name);
        BackgroundColor(adventurers[i].color.fontColor, adventurers[i].color.backColor);
        printf(" %d\n", adventurers[i].steps_counter);
        BackgroundColor(adventurers[i].color.backColor, adventurers[i].color.fontColor);
        printf("\nCantidad de estados por los cuales paso el aventurero '%s': ", adventurers[i].name);
        BackgroundColor(adventurers[i].color.fontColor, adventurers[i].color.backColor);
        printf(" %d\n", adventurers[i].total_states);
        printf("\n");
        fflush(stdout);
        RstColor();
    }
    while (getchar() != '\n')
        ; // Limpiar el búfer del teclado

    BackgroundColor(GREEN_COLOR, BLACK_COLOR);
    printf("En general el promedio de pasos y estados totales fueron respetivamente : %.4f - %.4f\n", (float)((adventurers[0].steps_counter + adventurers[1].steps_counter + adventurers[2].steps_counter + adventurers[3].steps_counter) / 4), (float)((adventurers[0].total_states + adventurers[1].total_states + adventurers[2].total_states + adventurers[3].total_states) / 4));
    printf("\n");
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