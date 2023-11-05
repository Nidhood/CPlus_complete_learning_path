#include "../include/MenusHeader.h"

void display_message(const char *message, uchar FontColor, uchar BgColor)
{
    size_t message_length = strlen(message);
    int total_width = 100; // Ancho total de la línea de separación
    size_t padding = (total_width - message_length) / 2;
    Cls()
    BackgroundColor(FontColor, BgColor);
    printf("\n##################################################################################################\n");
    printf("                                                                                                  \n");

    // Imprimir el mensaje centrado
    for (int i = 0; i < padding; i++)
        printf(" ");
    printf("%s", message);
    if (padding % 2 == 0)
    {
        for (int i = 0; i < padding - 2; i++)
            printf(" ");
    }
    else
    {
        for (int i = 0; i < padding; i++)
            printf(" ");
    }

    // Imprimir la línea entre el mensaje y el borde inferior
    printf("\n                                                                                                  \n");
    printf("##################################################################################################\n");
    RstColor()
    sleep(4);
    Cls()
}

int display_menu(MenuOptionsT menu)
{
    char valid_option;
    int option = 0;
    do
    {
        valid_option = 0;
        Cls()
            BackgroundColor(MAGENTA_COLOR, BLACK_COLOR);
        printf("\n%s\n", menu.menuDescription);
        BackgroundColor(CYAN_COLOR, BLACK_COLOR);
        for (int i = 0; i < menu.num_options; i++)
        {
            printf("\n%d. %s", menu.options[i].option_index, menu.options[i].optionDescription);
        }
        BackgroundColor(MAGENTA_COLOR, BLACK_COLOR);
        printf("\n\nDigite la opcion deseada: ");
        BackgroundColor(GREEN_COLOR, BLACK_COLOR);
        scanf("%d", &option);
        for (int i = 0; i < menu.num_options; i++)
        {
            if (menu.options[i].option_index == option)
            {
                valid_option = 1;
                break;
            }
        }
        if (!valid_option)
        {
            // Invalid option message.
            display_message("La opcion es incorrecta, intentelo de nuevo.", CYAN_COLOR, RED_COLOR);
        }
    } while (!valid_option);
    return option;
}

// Shows nice out message for the program :D .
void exitDisplay()
{
    Cls()
    BackgroundColor(YELLOW_COLOR, BLACK_COLOR);
    printf("\n###################################################################################################");
    printf("\n\n                               Muchas gracias por usar nuestro programa.\n");
    printf("\n                                         ¡¡¡ Vuelva pronto !!!\n");
    printf("\n###################################################################################################\n");
    sleep(4);
    RstColor()
    Cls()
}