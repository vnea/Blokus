#include <stdio.h>
#include <windows.h>

#include "../include/affichage.h"

void gotoligcol(int lig, int col)
{
    COORD coord = {col, lig};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_char_couleur(char c, int couleur)
{
    changer_print_couleur(couleur);
    printf("%c", c);
    reset_print_couleur();
}

void changer_print_couleur(int couleur)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), couleur << 4);
}
void reset_print_couleur()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
}
