#include "UtilHeader.h"

void BackgroundColor(uchar FontColor, uchar BgColor)
{
    char FG;
    char BG;
    if ((FontColor == NORMAL_COLOR) || (BgColor == NORMAL_COLOR))
    {
        printf("\033[0m");
        return;
    }
    switch (FontColor)
    {
    case BLACK_COLOR:
    {
        FG = (char)((FontColor & 0x0F) + 30);
        break;
    }
    case RED_COLOR:
    {
        FG = (char)((FontColor & 0x0F) + 31);
        break;
    }
    case GREEN_COLOR:
    {
        FG = (char)((FontColor & 0x0F) + 32);
        break;
    }
    case YELLOW_COLOR:
    {
        FG = (char)((FontColor & 0x0F) + 33);
        break;
    }
    case BLUE_COLOR:
    {
        FG = (char)((FontColor & 0x0F) + 34);
        break;
    }
    case MAGENTA_COLOR:
    {
        FG = (char)((FontColor & 0x0F) + 35);
        break;
    }
    case CYAN_COLOR:
    {
        FG = (char)((FontColor & 0x0F) + 36);
        break;
    }
    case WHITE_COLOR:
    {
        FG = (char)((FontColor & 0x0F) + 37);
        break;
    }
    default:
        printf("\x1b[0m");
        return;
    }
    switch (BgColor)
    {
    case BLACK_COLOR:
    {
        BG = (char)((BgColor & 0x0F) + 40);
        break;
    }
    case RED_COLOR:
    {
        BG = (char)((BgColor & 0x0F) + 41);
        break;
    }
    case GREEN_COLOR:
    {
        BG = (char)((BgColor & 0x0F) + 42);
        break;
    }
    case YELLOW_COLOR:
    {
        BG = (char)((BgColor & 0x0F) + 43);
        break;
    }
    case BLUE_COLOR:
    {
        BG = (char)((BgColor & 0x0F) + 44);
        break;
    }
    case MAGENTA_COLOR:
    {
        BG = (char)((BgColor & 0x0F) + 45);
        break;
    }
    case CYAN_COLOR:
    {
        BG = (char)((BgColor & 0x0F) + 46);
        break;
    }
    case WHITE_COLOR:
    {
        BG = (char)((BgColor & 0x0F) + 47);
        break;
    }
    default:
        printf("\x1b[0m");
        return;
    }
    printf("\x1b[1;%d;%dm", FG, BG);
}

void Delay(int Seconds)
{
    int ms = 1000 * Seconds;
    clock_t StartTime = clock();
    while (clock() < (StartTime + ms))
    {
    }
}