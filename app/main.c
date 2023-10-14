#include <stdio.h>  // input and output streams.
#include <stdlib.h> // EXIT_SUCCESS return.
#include "../include/MenusHeader.h"
#include "../include/MapHeader.h"
#include "../include/MazeRunnerHeader.h"

// Global Variables:
#define MAX_ADVENTURERS 4

// Macros:

#ifdef _WIN32

// Path prefix for Windows
#define FILE_PATH_PREFIX "..\\Maps\\"
#else

// Path prefix for Unix-based systems (Linux)
#define FILE_PATH_PREFIX "Maps/"
#endif

// Steps to implement the code:

// 2. Create map (based on the selected one).

// 3. Loop to animate the Maze runner.

// 4. End program.

int main()
{
    // Declare variables:
    int menu_option, map_option = 0, validation_counter = 0;
    char out_validation, goal_validation = 1, option = '\0', goal_validation_vector[MAX_ADVENTURERS] = {0}; // False by default.

    OptionT main_menu_options[] = {
        {1, "Seleccionar mapa."},
        {2, "Dibujar mapa."},
        {3, "Resolver laberinto."},
        {4, "Salir."}};

    OptionT map_menu_options[] = {
        {1, "Mapa 1."},
        {2, "Mapa 2."},
        {3, "Mapa 3."},
        {4, "Mapa 4."},
        {5, "Mapa 5."}};

    MenuOptionsT main_menu = {
        .menuDescription = "Seleccione la opcion que desea realizar.",
        .options = {main_menu_options[0], main_menu_options[1], main_menu_options[2], main_menu_options[3]},
        .num_options = 4};

    MenuOptionsT map_menu = {
        .menuDescription = "Seleccione la opcion que desea realizar.",
        .options = {map_menu_options[0], map_menu_options[1], map_menu_options[2], map_menu_options[3], map_menu_options[4]},
        .num_options = 5};

    MapT maps[] = {
        createMap("Mapa 1", "Mapa 1", FILE_PATH_PREFIX "Map1.txt"),
        createMap("Mapa 2", "Mapa 2", FILE_PATH_PREFIX "Map2.txt"),
        createMap("Mapa 3", "Mapa 3", FILE_PATH_PREFIX "Map3.txt"),
        createMap("Mapa 4", "Mapa 4", FILE_PATH_PREFIX "Map4.txt"),
        createMap("Mapa 5", "Mapa 5", FILE_PATH_PREFIX "Map5.txt")};

    AdventurerT adventurers[] = {
        setAdventurer("Thomas", WHITE_COLOR, RED_COLOR, 0 ),
        setAdventurer("Newt", GREEN_COLOR, BLUE_COLOR, 0),
        setAdventurer("Minho", BLUE_COLOR, MAGENTA_COLOR, 0),
        setAdventurer("Chuck", MAGENTA_COLOR, YELLOW_COLOR, 0)};

    // Welcome message.
    // display_message("¡¡¡ Bienvenidos aventureros al laberinto !!!", YELLOW_COLOR, BLACK_COLOR);
    do
    {
        out_validation = 0;

        // 1. Display menu:
        menu_option = display_menu(main_menu);

        switch (menu_option)
        {
        case 1:
            map_option = display_menu(map_menu);
            if (map_option >= 1 && map_option <= 5)
            {
                // 2. Get map.
                map_option = getMap(&maps[map_option - 1], adventurers, map_option, 1);
            }
            else
            {
                map_option = 0;
            }
            if (map_option != 0)
            {
                // display_message("El mapa ha sido cargado correctamente.", GREEN_COLOR, BLACK_COLOR);
            }
            else
            {
                display_message("El mapa no ha sido cargado, intentelo de nuevo.", RED_COLOR, BLACK_COLOR);
            }
            break;

        case 2:
            if (map_option >= 1 && map_option <= 5)
            {
                drawProbabilitiesMap(maps[map_option - 1], adventurers, MAGENTA_COLOR, CYAN_COLOR, WHITE_COLOR, RED_COLOR);
                printf("\n\n");
                drawMap(maps[map_option - 1], adventurers, MAGENTA_COLOR, CYAN_COLOR, WHITE_COLOR, RED_COLOR);

                printf("\nDigite cualquier opcion para continuar: ");
                scanf(" %c", &option);
            }
            else
            {
                // Invalid option message.
                display_message("Debe seleccionar un mapa valido primero, intentelo de nuevo.", CYAN_COLOR, RED_COLOR);
            }
            break;

        case 3:
            if (map_option >= 1 && map_option <= 5)
            {

                // 3. Loop to animate the Maze runner.
                while (goal_validation)
                {
                    for (int i = 0; i < MAX_ADVENTURERS; i++)
                    {
                        drawMap(maps[map_option - 1], adventurers, MAGENTA_COLOR, CYAN_COLOR, WHITE_COLOR, RED_COLOR);
                        goal_validation_vector[i] = adventurersMovement(&adventurers[i], &maps[map_option - 1]);
                        updateMap(adventurers[i], &maps[map_option - 1]);
                        validation_counter++;
                        if (goal_validation_vector[i])
                        {
                            validation_counter++;
                        }
                        if (i == MAX_ADVENTURERS - 1)
                        {
                            if (validation_counter == MAX_ADVENTURERS)
                            {
                                goal_validation = 0;
                            }
                            validation_counter = 0;
                        }
                    }
                    Delay(100);
                }
                Cls()
                    drawWinMap(maps[map_option - 1], adventurers, BLUE_COLOR, GREEN_COLOR, MAGENTA_COLOR, CYAN_COLOR);

                // Initialize goal validation vector to 0.
                for (int i = 0; i < MAX_ADVENTURERS; i++)
                {
                    goal_validation_vector[i] = 0;
                }
            }
            else
            {
                // Invalid option message.
                display_message("Debe seleccionar un mapa valido primero, intentelo de nuevo.", CYAN_COLOR, RED_COLOR);
            }
            break;

        case 4:
            out_validation = 1;
            break;

        default:
            break;
        }
    } while (!out_validation);

    // 4. End program.
    exitDisplay();
    return EXIT_SUCCESS;
}