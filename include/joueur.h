#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "piece.h"

#define NB_MAX_JOUEURS 4
#define TAILLE_PSEUDO_MAX 64

typedef struct joueur
{
    char pseudo[TAILLE_PSEUDO_MAX];
    t_piece pieces[NB_PIECES_MAX];
    int premier_coup;

} t_joueur;

void initialiser_joueur(t_joueur *joueur, char pseudo[TAILLE_PSEUDO_MAX], t_piece pieces[NB_PIECES_MAX], int couleur_pieces);

#endif // JOUEUR_H_INCLUDED
