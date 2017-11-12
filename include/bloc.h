#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED

#include "coord.h"

typedef struct piece t_piece;
typedef struct bloc
{
    t_coord coord;

    char est_un_angle;
    t_piece *piece;
} t_bloc;

void rotation_gauche_bloc(t_bloc *bloc);
void rotation_droite_bloc(t_bloc *bloc);
void inverser_bloc(t_bloc *bloc);

#endif // BLOC_H_INCLUDED
