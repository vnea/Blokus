#include "../include/bloc.h"

void rotation_gauche_bloc(t_bloc *bloc)
{
    int valeur_x_de_base = bloc->x;
    bloc->x = bloc->y;
    bloc->y = -valeur_x_de_base;
}

void rotation_droite_bloc(t_bloc *bloc)
{
    int valeur_x_de_base = bloc->x;
    bloc->x = -bloc->y;
    bloc->y = valeur_x_de_base;
}
