#include <stdio.h>
#include <windows.h>

#include "../include/affichage.h"

void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_char_couleur(char c, int couleur)
{
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), couleur << 4);
    printf("%c", c);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
}
