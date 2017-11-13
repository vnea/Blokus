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

#endif // BLOC_H_INCLUDED
