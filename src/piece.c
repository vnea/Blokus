#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/piece.h"

void initialiser_piece(t_piece *piece, char symbole, t_bloc blocs[NB_BLOCS_MAX], int nb_blocs)
{
    piece->symbole = symbole;
    piece->couleur = 1;

    piece->nb_blocs = nb_blocs;
    int num_bloc;
    for (num_bloc = 0; num_bloc < piece->nb_blocs; num_bloc++)
    {
        piece->blocs[num_bloc].coord = blocs[num_bloc].coord;
        piece->blocs[num_bloc].est_un_angle = blocs[num_bloc].est_un_angle;
        piece->blocs[num_bloc].piece = blocs[num_bloc].piece;
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

    int num_piece;
    for (num_piece = 0; num_piece < NB_PIECES_MAX; num_piece++)
    {
        FILE *fichier_piece = fopen(chemin_vers_pieces[num_piece], "r");
        if (fichier_piece)
        {
            char symbole;
            fscanf(fichier_piece, "%c", &symbole);

            int nb_blocs;
            fscanf(fichier_piece, "%d", &nb_blocs);

            t_bloc blocs[NB_BLOCS_MAX];
            int num_bloc;
            for (num_bloc = 0; num_bloc < nb_blocs; num_bloc++)
            {
                fscanf(fichier_piece, "%d %d %c", &blocs[num_bloc].coord.x, &blocs[num_bloc].coord.y, &blocs[num_bloc].est_un_angle);
                blocs[num_bloc].piece = &pieces[num_piece];
            }

            initialiser_piece(&pieces[num_piece], symbole, blocs, nb_blocs);
        }
        fclose(fichier_piece);
    }
}


void rotation_gauche_piece(t_piece *piece)
{
    int num_bloc;
    for (num_bloc = 0; num_bloc < piece->nb_blocs; num_bloc++)
    {
        t_bloc *bloc_courant = &piece->blocs[num_bloc];
        int valeur_x_de_base = bloc_courant->coord.x;
        bloc_courant->coord.x = bloc_courant->coord.y;
        bloc_courant->coord.y = -valeur_x_de_base;
    }
}

void rotation_droite_piece(t_piece *piece)
{
    int num_bloc;
    for (num_bloc = 0; num_bloc < piece->nb_blocs; num_bloc++)
    {
        t_bloc *bloc_courant = &piece->blocs[num_bloc];
        int valeur_x_de_base = bloc_courant->coord.x;
        bloc_courant->coord.x = -bloc_courant->coord.y;
        bloc_courant->coord.y = valeur_x_de_base;
    }
}

void inverser_piece(t_piece *piece)
{
    int num_bloc;
    for (num_bloc = 0; num_bloc < piece->nb_blocs; num_bloc++)
    {
        t_bloc *bloc_courant = &piece->blocs[num_bloc];
        bloc_courant->coord.x = -bloc_courant->coord.x;
    }
}

t_bloc* trouver_bloc_plus_haut_gauche_piece(t_piece *piece)
{
    t_bloc *bloc_plus_haut_gauche = &piece->blocs[0];

    int num_bloc;
    for (num_bloc = 1; num_bloc < piece->nb_blocs; num_bloc++)
    {
        t_bloc *bloc_courant = &piece->blocs[num_bloc];
        if (bloc_courant->coord.y < bloc_plus_haut_gauche->coord.y &&
            bloc_courant->coord.x < bloc_plus_haut_gauche->coord.x)
        {
            bloc_plus_haut_gauche = bloc_courant;
        }
    }

    return bloc_plus_haut_gauche;
}
