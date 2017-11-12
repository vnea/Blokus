#include "../include/bloc.h"

void rotation_gauche_bloc(t_bloc *bloc)
{
    int valeur_x_de_base = bloc->coord.x;
    bloc->coord.x = bloc->coord.y;
    bloc->coord.y = -valeur_x_de_base;
}

void rotation_droite_bloc(t_bloc *bloc)
{
    int valeur_x_de_base = bloc->coord.x;
    bloc->coord.x = -bloc->coord.y;
    bloc->coord.y = valeur_x_de_base;
}

void inverser_bloc(t_bloc *bloc)
{
    bloc->coord.x = -bloc->coord.x;
}
