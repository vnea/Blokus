#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#define NB_LIGNES 20
#define NB_COLONNES 20

#include "piece.h"

typedef struct plateau
{
    t_bloc* damier[NB_LIGNES][NB_COLONNES];
} t_plateau;

void initialiser_plateau(t_plateau *plateau);

int peut_poser_piece_dans_plateau(t_plateau *plateau, t_piece *piece, int pos_x, int pos_y);
int bloc_angle_d_une_piece_est_valide(t_plateau *plateau, t_piece *piece, int pos_x, int pos_y);
void poser_piece(t_plateau *plateau, t_piece *piece, int pos_x, int pos_y);

void afficher_plateau(t_plateau *plateau);

#endif // PLATEAU_H_INCLUDED
