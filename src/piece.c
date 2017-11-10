#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/piece.h"

void initialiser_piece(t_piece *piece, char symbole, t_bloc blocs[NB_BLOCS_MAX], int nb_blocs)
{
    piece->symbole = symbole;
    piece->couleur = 1;

    piece->nb_blocs = nb_blocs;
    int i;
    for (i = 0; i < piece->nb_blocs; i++)
    {
        piece->blocs[i].x = blocs[i].x;
        piece->blocs[i].y = blocs[i].y;
        piece->blocs[i].est_un_angle = blocs[i].est_un_angle;
        piece->blocs[i].piece = blocs[i].piece;
    }
}

void charger_pieces(t_piece pieces[NB_PIECES_MAX])
{
    char* chemin_vers_pieces[NB_PIECES_MAX] =
    {
        "ressources/pieces/A.txt",
        "ressources/pieces/B.txt",
        "ressources/pieces/C.txt",
        "ressources/pieces/D.txt",
        "ressources/pieces/E.txt",
        "ressources/pieces/F.txt",
        "ressources/pieces/G.txt",
        "ressources/pieces/H.txt",
        "ressources/pieces/I.txt",
        "ressources/pieces/J.txt",
        "ressources/pieces/K.txt",
        "ressources/pieces/L.txt",
        "ressources/pieces/M.txt",
        "ressources/pieces/N.txt",
        "ressources/pieces/O.txt",
        "ressources/pieces/P.txt",
        "ressources/pieces/Q.txt",
        "ressources/pieces/R.txt",
        "ressources/pieces/S.txt",
        "ressources/pieces/T.txt",
        "ressources/pieces/U.txt"
    };

    int nb_pieces;
    for (nb_pieces = 0; nb_pieces < NB_PIECES_MAX; nb_pieces++)
    {
        FILE *fichier_piece = fopen(chemin_vers_pieces[nb_pieces], "r");
        if (fichier_piece)
        {
            char symbole;
            fscanf(fichier_piece, "%c", &symbole);

            int nb_blocs;
            fscanf(fichier_piece, "%d", &nb_blocs);

            t_bloc blocs[NB_BLOCS_MAX];
            int i;
            for (i = 0; i < nb_blocs; i++)
            {
                fscanf(fichier_piece, "%d %d %c", &blocs[i].x, &blocs[i].y, &blocs[i].est_un_angle);
                blocs[i].piece = &pieces[nb_pieces];
            }

            initialiser_piece(&pieces[nb_pieces], symbole, blocs, nb_blocs);
        }
        fclose(fichier_piece);
    }
}


void rotation_gauche_piece(t_piece *piece)
{
    int i;
    for (i = 0; i < piece->nb_blocs; i++)
    {
        rotation_gauche_bloc(piece->blocs);
    }
}

void rotation_droite_piece(t_piece *piece)
{
    int i;
    for (i = 0; i < piece->nb_blocs; i++)
    {
        rotation_droite_bloc(piece->blocs);
    }
}
