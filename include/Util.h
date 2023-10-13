#ifndef INTELLI_UTIL_H
#define INTELLI_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NORMAL_COLOR 0xF0
#define BLACK_COLOR 0x10
#define RED_COLOR 0x20
#define GREEN_COLOR 0x30
#define YELLOW_COLOR 0x40
#define BLUE_COLOR 0x50
#define MAGENTA_COLOR 0x60
#define CYAN_COLOR 0x70
#define WHITE_COLOR 0x80

#define Cls() printf("\033[H\033[J"); // ANSI code to clear screen.
#ifdef _WIN32

// Para sistemas Windows
#define Pause() system("pause");
#else

#define Pause() system("read -n 1 -s -p \"Press any key to continue...\"");

#define RstColor() BackgroundColor(NORMAL_COLOR, NORMAL_COLOR);

#endif // _WIN32

#define RstColor() BackgroundColor(NORMAL_COLOR, NORMAL_COLOR);

typedef unsigned char uchar;

void BackgroundColor(uchar FontColor, uchar BgColor);
void Delay(int Seconds);

#endif // INTELLI_UTIL_H