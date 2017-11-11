#include <string.h>
#include "../include/joueur.h"

void initialiser_joueur(t_joueur *joueur, char pseudo[TAILLE_PSEUDO_MAX], t_piece pieces[NB_PIECES_MAX], int couleur_pieces)
{
    strcpy(joueur->pseudo, pseudo);

    int i;
    for (i = 0; i < NB_PIECES_MAX; i++)
    {
        t_piece *piece_courante = &joueur->pieces[i];
        piece_courante->symbole = pieces[i].symbole;
        piece_courante->couleur = couleur_pieces;
        int j;
        for (j = 0; j < pieces[i].nb_blocs; j++)
        {
            piece_courante->blocs[j].coord = pieces[i].blocs[j].coord;
            piece_courante->blocs[j].est_un_angle = pieces[i].blocs[j].est_un_angle;
            piece_courante->blocs[j].piece = pieces[i].blocs[j].piece;
        }
        piece_courante->nb_blocs = pieces[i].nb_blocs;
    }

    joueur->premier_coup = 1;
}
