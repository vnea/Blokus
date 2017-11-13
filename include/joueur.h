#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#define NB_MAX_JOUEURS 4
#define TAILLE_PSEUDO_MAX 64

#define NB_LIGNES_PLATEAU_JOUEUR 12
#define NB_COLONNES_PLATEAU_JOUEUR 19

#include "piece.h"
#include "plateau.h"

typedef struct joueur
{
    char pseudo[TAILLE_PSEUDO_MAX];
    int premier_coup;
    int a_perdu;

    t_piece pieces[NB_PIECES_MAX];
    int piece_deja_posee[NB_PIECES_MAX];

    t_bloc *plateau_selection_piece[NB_LIGNES_PLATEAU_JOUEUR][NB_COLONNES_PLATEAU_JOUEUR];
} t_joueur;

void initialiser_joueur(t_joueur *joueur, char pseudo[TAILLE_PSEUDO_MAX], t_piece pieces[NB_PIECES_MAX], int couleur_pieces);
int peut_encore_jouer(t_joueur *joueur, t_plateau *plateau);
void poser_piece_dans_plateau_selection_piece(t_joueur *joueur, t_piece *piece, t_coord *coord);
void poser_toutes_les_pieces_dans_plateau_selection_piece(t_joueur *joueur);
void afficher_pieces_joueur(t_joueur *joueur);


#endif // JOUEUR_H_INCLUDED
