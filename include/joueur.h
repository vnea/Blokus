#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "piece.h"
#include "plateau.h"

#define TAILLE_PSEUDO_MAX 64

#define NB_LIGNES_PLATEAU_JOUEUR 12
#define NB_COLONNES_PLATEAU_JOUEUR 19

#define NB_LIGNES_PLATEAU_PIECE 12
#define NB_COLONNES_PLATEAU_PIECE 12

typedef struct joueur
{
    char pseudo[TAILLE_PSEUDO_MAX];
    int premier_coup;
    int peut_jouer;
    int couleur_pieces;
    int est_ia;

    t_piece pieces[NB_PIECES_MAX];
    int piece_deja_posee[NB_PIECES_MAX];
    t_bloc *plateau_selection_pieces[NB_LIGNES_PLATEAU_JOUEUR][NB_COLONNES_PLATEAU_JOUEUR];

    t_piece *piece_selectionnee;
    t_bloc *plateau_piece_selectionnee[NB_LIGNES_PLATEAU_PIECE][NB_COLONNES_PLATEAU_PIECE];
} t_joueur;

void initialiser_joueur(t_joueur *joueur, char pseudo[TAILLE_PSEUDO_MAX], t_piece pieces[NB_PIECES_MAX], int couleur_pieces, int est_ia);
int peut_jouer_joueur(t_joueur *joueur, t_plateau *plateau);
int nb_pieces_restantes_joueur(t_joueur *joueur);

void initialiser_plateau_selection_pieces(t_joueur *joueur);
void poser_piece_dans_plateau_selection_pieces(t_joueur *joueur, t_piece *piece, t_coord *coord);
void afficher_pieces_joueur(t_joueur *joueur);

void initialiser_plateau_piece_selectionnee(t_joueur *joueur);
void poser_piece_dans_plateau_piece_selectionnee(t_joueur *joueur, t_piece *piece);
void afficher_piece_selectionnee_joueur(t_joueur *joueur);

#endif // JOUEUR_H_INCLUDED
