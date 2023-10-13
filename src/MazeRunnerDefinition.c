#include "../include/MazeRunnerHeader.h"

// With the new adventurers positions, update the map.
// void updateMap(AdventurerT adventurer, MapT *map);

// Steps to implement the FSM:

// 1. Check the current position.
// 2. Check if the adventurer can move (move if there is not wall, if is not go to the next state).
// 3. Turn the adventurer to the right.

// Define the behaviors of adventurers.
char adventurersMovement(AdventurerT *adventurer, MapT *map)
{
    // Initialize the seed to generate different random numbers in each execution
    srand(time(NULL));
    int randX = 0, randY = 0;

    // FSM (basic but works):
    switch (adventurer->currentState)
    {
    case STATE_INITIAL:

        // Obtain data from the current cell (map).
        adventurer->moveValidation.up = (char)(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y + 1].value != '*' && strcmp(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y + 1].adventurers[adventurer->adventurer_index].adventurer, adventurer->name) != 0);
        adventurer->moveValidation.down = (char)(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y - 1].value != '*' && strcmp(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y - 1].adventurers[adventurer->adventurer_index].adventurer, adventurer->name) != 0);
        adventurer->moveValidation.right = (char)(map->matrix[adventurer->currentLocation.x + 1][adventurer->currentLocation.y].value != '*' && strcmp(map->matrix[adventurer->currentLocation.x + 1][adventurer->currentLocation.y].adventurers[adventurer->adventurer_index].adventurer, adventurer->name) != 0);
        adventurer->moveValidation.left = (char)(map->matrix[adventurer->currentLocation.x - 1][adventurer->currentLocation.y].value != '*' && strcmp(map->matrix[adventurer->currentLocation.x - 1][adventurer->currentLocation.y].adventurers[adventurer->adventurer_index].adventurer, adventurer->name) != 0);

        // Transition to the next state
        if ((char)(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y + 1].value == 'O') || (char)(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y - 1].value == 'O') || (char)(map->matrix[adventurer->currentLocation.x + 1][adventurer->currentLocation.y].value == 'O') || (char)(map->matrix[adventurer->currentLocation.x - 1][adventurer->currentLocation.y].value == 'O'))
        {
            if ((char)(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y + 1].value == 'O'))
            {
                setAdventurerPosition("Arriba", adventurer);
            }
            else if ((char)(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y - 1].value == 'O'))
            {
                setAdventurerPosition("Abajo", adventurer);
            }
            else if ((char)(map->matrix[adventurer->currentLocation.x + 1][adventurer->currentLocation.y].value == 'O'))
            {
                setAdventurerPosition("Derecha", adventurer);
            }
            else if ((char)(map->matrix[adventurer->currentLocation.x - 1][adventurer->currentLocation.y].value == 'O'))
            {
                setAdventurerPosition("Iquierda", adventurer);
            }
            adventurer->currentState = STATE_FINAL;
        }
        else if (
            validateClash(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y + 1].value) ||
            validateClash(map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y - 1].value) ||
            validateClash(map->matrix[adventurer->currentLocation.x + 1][adventurer->currentLocation.y].value) ||
            validateClash(map->matrix[adventurer->currentLocation.x - 1][adventurer->currentLocation.y].value))
        {
            if (adventurer->adventurer_colitions <= 3)
            {
                adventurer->adventurer_colitions++;
                adventurer->currentState = STATE_CLASH;
            }
            else
            {
                adventurer->adventurer_colitions = 0;
                adventurer->currentState = STATE_REAPPEAR;
            }
        }
        else if (adventurer->moveValidation.up || adventurer->moveValidation.down || adventurer->moveValidation.right || adventurer->moveValidation.left)
        {
            adventurer->route[adventurer->steps_counter].x = adventurer->currentLocation.x;
            adventurer->route[adventurer->steps_counter].y = adventurer->currentLocation.y;
            adventurer->steps_counter++;
            adventurer->currentState = STATE_CHECK_FORWARD;
        }
        else
        {
            adventurer->currentState = STATE_MOVE_BACKWARDS;
        }
        adventurer->total_states++;
        return 1;

    case STATE_CHECK_FORWARD:

        // Check if the adventurer can move forward (no wall):
        if (adventurer->moveValidation.up && strcmp(adventurer->direction.description, "Arriba") == 0)
        {
            // Move forward (up):
            adventurer->currentLocation.y += 1;

            // Transition to the initial state:
            adventurer->currentState = STATE_INITIAL;
        }
        else if (adventurer->moveValidation.down && strcmp(adventurer->direction.description, "Abajo") == 0)
        {
            // Move forward (down):
            adventurer->currentLocation.y -= 1;

            // Transition to the initial state:
            adventurer->currentState = STATE_INITIAL;
        }
        else if (adventurer->moveValidation.right && strcmp(adventurer->direction.description, "Derecha") == 0)
        {
            // Move forward (right):
            adventurer->currentLocation.x += 1;

            // Transition to the initial state:
            adventurer->currentState = STATE_INITIAL;
        }
        else if (adventurer->moveValidation.left && strcmp(adventurer->direction.description, "Izquierda") == 0)
        {
            // Move forward (left):
            adventurer->currentLocation.x -= 1;

            // Transition to the initial state:
            adventurer->currentState = STATE_INITIAL;
        }
        else
        {
            // Transition to the turn right state:
            if (adventurer->moveValidation.left && strcmp(adventurer->direction.description, "Arriba") == 0)
            {
                adventurer->currentState = STATE_TURN_LEFT;
            }
            else if (adventurer->moveValidation.right && strcmp(adventurer->direction.description, "Abajo") == 0)
            {
                adventurer->currentState = STATE_TURN_LEFT;
            }
            else if (adventurer->moveValidation.up && strcmp(adventurer->direction.description, "Derecha") == 0)
            {
                adventurer->currentState = STATE_TURN_LEFT;
            }
            else if (adventurer->moveValidation.down && strcmp(adventurer->direction.description, "Izquierda") == 0)
            {
                adventurer->currentState = STATE_TURN_LEFT;
            }
            else
            {
                adventurer->currentState = STATE_TURN_RIGHT;
            }
        }
        adventurer->total_states++;
        return 1;

    case STATE_MOVE_BACKWARDS:

        // Move backwards (last location):
        if (adventurer->steps_counter > 0)
        {
            adventurer->steps_counter--;

            // Clear the previous position:
            map->matrix[adventurer->currentLocation.x][adventurer->currentLocation.y].value = ' ';

            // Change the adventurer's direction:
            if (adventurer->currentLocation.x > adventurer->route[adventurer->steps_counter].x)
            {
                setAdventurerPosition("Izquierda", adventurer);
            }
            else if (adventurer->currentLocation.x < adventurer->route[adventurer->steps_counter].x)
            {
                setAdventurerPosition("Derecha", adventurer);
            }
            else if (adventurer->currentLocation.y > adventurer->route[adventurer->steps_counter].y)
            {
                setAdventurerPosition("Abajo", adventurer);
            }
            else if (adventurer->currentLocation.y < adventurer->route[adventurer->steps_counter].y)
            {
                setAdventurerPosition("Arriba", adventurer);
            }

            // Update the current location based on the route:
            adventurer->currentLocation.x = adventurer->route[adventurer->steps_counter].x;
            adventurer->currentLocation.y = adventurer->route[adventurer->steps_counter].y;

            // Returns to the initial state:
            adventurer->currentState = STATE_INITIAL;
        }
        else
        {
            // There is no more stepst to go backwards, so we change direction:
            adventurer->currentState = STATE_REAPPEAR;
        }
        adventurer->total_states++;
        return 1;

    case STATE_TURN_LEFT:

        // Turn the adventurer to the left:
        if (strcmp(adventurer->direction.description, "Arriba") == 0)
        {
            setAdventurerPosition("Izquierda", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Abajo") == 0)
        {
            setAdventurerPosition("Derecha", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Derecha") == 0)
        {
            setAdventurerPosition("Arriba", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Izquierda") == 0)
        {
            setAdventurerPosition("Abajo", adventurer);
        }

        // Transition to the initial state:
        adventurer->currentState = STATE_INITIAL;
        adventurer->total_states++;
        return 1;

    case STATE_TURN_RIGHT:

        // Turn the adventurer to the right
        if (strcmp(adventurer->direction.description, "Arriba") == 0)
        {
            setAdventurerPosition("Derecha", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Abajo") == 0)
        {
            setAdventurerPosition("Izquierda", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Derecha") == 0)
        {
            setAdventurerPosition("Abajo", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Izquierda") == 0)
        {
            setAdventurerPosition("Arriba", adventurer);
        }

        // Transition to the initial state
        adventurer->currentState = STATE_INITIAL;
        adventurer->total_states++;
        return 1;

    case STATE_CLASH:

        // Turn the adventurer to the oposite direction:
        if (strcmp(adventurer->direction.description, "Arriba") == 0)
        {
            setAdventurerPosition("Abajo", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Abajo") == 0)
        {
            setAdventurerPosition("Arriba", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Derecha") == 0)
        {
            setAdventurerPosition("Izquierda", adventurer);
        }
        else if (strcmp(adventurer->direction.description, "Izquierda") == 0)
        {
            setAdventurerPosition("Derecha", adventurer);
        }

        // Transition to the initial state
        adventurer->currentState = STATE_MOVE_BACKWARDS;
        adventurer->total_states++;
        return 1;

    case STATE_REAPPEAR:

        // Find a random position without obstacles:
        do
        {
            randX = rand() % MAX_SIZE;
            randY = rand() % MAX_SIZE;
        } while (map->matrix[randX][randY].value != ' ');

        // Update the adventurer's position:
        adventurer->currentLocation.x = randX;
        adventurer->currentLocation.y = randY;

        // Clear the route and steps counter:
        cleanAdventurerRoute(map, *adventurer);

        // Return to the initial state:
        adventurer->currentState = STATE_INITIAL;
        adventurer->total_states++;
        return 1;

    case STATE_FINAL:

        // Make the position of the winning player invisible, so that it does not hinder the other adventurers from winning.
        cleanAdventurerRoute(map, *adventurer);
        adventurer->total_states++;
        return 0;

    default:
        return 1;
    }
}

// 2. With the new adventurers positions, update the map.
void updateMap(AdventurerT adventurer, MapT *map)
{
    // If the adventurer has moved forward
    if (adventurer.steps_counter > 0)
    {
        // Clear the previous position
        map->matrix[adventurer.route[adventurer.steps_counter - 1].x][adventurer.route[adventurer.steps_counter - 1].y].value = ' ';
    }

    if (adventurer.currentState == STATE_FINAL)
    {

        // Update the new position with the adventurer's symbol (win codition).
        map->matrix[adventurer.currentLocation.x][adventurer.currentLocation.y].value = ' ';
        strcpy(map->matrix[adventurer.currentLocation.x][adventurer.currentLocation.y].adventurers[adventurer.adventurer_index].adventurer, "\0");
        map->matrix[adventurer.currentLocation.x][adventurer.currentLocation.y].lastIndex = -1;
    }
    else
    {
        // Update the new position with the adventurer's symbol.
        map->matrix[adventurer.currentLocation.x][adventurer.currentLocation.y].value = adventurer.direction.symbol[0];
        map->matrix[adventurer.currentLocation.x][adventurer.currentLocation.y].lastIndex = adventurer.adventurer_index;

        // Leave the mark in the new position.
        strcpy(map->matrix[adventurer.currentLocation.x][adventurer.currentLocation.y].adventurers[adventurer.adventurer_index].adventurer, adventurer.name);
    }
}

char validateClash(const char validateValue)
{
    if (validateValue == '>')
    {
        return 1;
    }
    else if (validateValue == '<')
    {
        return 1;
    }
    else if (validateValue == 'V')
    {
        return 1;
    }
    else if (validateValue == '^')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void cleanAdventurerRoute(MapT *map, AdventurerT adventurer)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_SIZE; ++j)
        {
            if (strcmp(map->matrix[i][j].adventurers[adventurer.adventurer_index].adventurer, adventurer.name) == 0)
            {
                strcat(map->matrix[i][j].adventurers[adventurer.adventurer_index].adventurer, "\0");
                map->matrix[i][j].value = ' ';
                map->matrix[i][j].lastIndex = -1;
            }
        }
    }
}
