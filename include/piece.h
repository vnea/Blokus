#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include <stddef.h>

#include "bloc.h"

#define NB_PIECES_MAX 21
#define NB_BLOCS_MAX 5

typedef struct bloc t_bloc;
typedef struct piece
{
    char symbole;
    int couleur;

    t_bloc blocs[NB_BLOCS_MAX];
    int nb_blocs;
} t_piece;

void initialiser_piece(t_piece *piece, char symbole, t_bloc blocs[NB_BLOCS_MAX], int nb_blocs);
void copier_piece(t_piece *source, t_piece *destination);
void charger_pieces(t_piece pieces[NB_PIECES_MAX]);

void rotation_gauche_piece(t_piece *piece);
void rotation_droite_piece(t_piece *piece);
void inverser_piece(t_piece *piece);

t_bloc* trouver_bloc_plus_haut_gauche_piece(t_piece *piece);

#endif // PIECE_H_INCLUDED
