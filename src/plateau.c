#include <stdio.h>

#include "../include/plateau.h"

void initialiser_plateau(t_plateau *plateau)
{
    int index_ligne;
    for (index_ligne = 0; index_ligne < NB_LIGNES; index_ligne++)
    {
        int index_colonne;
        for (index_colonne = 0; index_colonne < NB_COLONNES; index_colonne++)
        {
            plateau->damier[index_ligne][index_colonne] = NULL;
        }
    }
}

int peut_poser_piece_dans_plateau(t_plateau *plateau, t_piece *piece, int pos_x, int pos_y)
{
    int i;
    for (i = 0; i < piece->nb_blocs; i++)
    {
        t_bloc *bloc_courant = &piece->blocs[i];
        int pos_x_piece_dans_plateau = bloc_courant->x + pos_x;
        int pos_y_piece_dans_plateau = bloc_courant->y + pos_y;

        // Verifier si le bloc est bien dans le plateau
        if (pos_x_piece_dans_plateau < 0 || pos_x_piece_dans_plateau > NB_COLONNES ||
            pos_y_piece_dans_plateau < 0 || pos_y_piece_dans_plateau > NB_LIGNES)
        {
           return 0;
        }

        // Verifier si le bloc n'est pas sur un autre bloc
        if (plateau->damier[pos_y_piece_dans_plateau][pos_x_piece_dans_plateau])
        {
            return 0;
        }

        // Verifier que les blocs adjacents sont d'une couleur différente

        // Bloc haut
        int pos_y_bloc_haut = pos_y_piece_dans_plateau - 1;
        if (pos_y_bloc_haut > 0)
        {
            t_bloc *bloc_haut = plateau->damier[pos_y_bloc_haut][pos_x_piece_dans_plateau];
            if (bloc_haut && bloc_haut->piece->couleur == piece->couleur)
            {
                return 0;
            }
        }

        // Bloc bas
        int pos_y_bloc_bas = pos_y_piece_dans_plateau + 1;
        if (pos_y_bloc_bas < NB_LIGNES)
        {
            t_bloc *bloc_bas = plateau->damier[pos_y_bloc_bas][pos_x_piece_dans_plateau];
            if (bloc_bas && bloc_bas->piece->couleur == piece->couleur)
            {
                return 0;
            }
        }

        // Bloc gauche
        int pos_x_bloc_gauche = pos_x_piece_dans_plateau - 1;
        if (pos_x_bloc_gauche > 0)
        {
            t_bloc *bloc_gauche = plateau->damier[pos_y_piece_dans_plateau][pos_x_bloc_gauche];
            if (bloc_gauche && bloc_gauche->piece->couleur == piece->couleur)
            {
                return 0;
            }
        }

        // Bloc droite
        int pos_x_bloc_droite = pos_x_piece_dans_plateau + 1;
        if (pos_x_bloc_droite < NB_COLONNES)
        {
            t_bloc *bloc_droite = plateau->damier[pos_y_piece_dans_plateau][pos_x_bloc_droite];
            if (bloc_droite && bloc_droite->piece->couleur == piece->couleur)
            {
                return 0;
            }
        }
    }

    // Verifier qu'un des angles est OK
    return bloc_angle_d_une_piece_est_valide(plateau, piece, pos_x, pos_y);
}

int bloc_angle_d_une_piece_est_valide(t_plateau *plateau, t_piece *piece, int pos_x, int pos_y)
{
    int i;
    for (i = 0; i < piece->nb_blocs; i++)
    {
        t_bloc *bloc_courant = &piece->blocs[i];
        int pos_x_piece_dans_plateau = bloc_courant->x + pos_x;
        int pos_y_piece_dans_plateau = bloc_courant->y + pos_y;

        if (bloc_courant->est_un_angle)
        {
            int pos_y_bloc_haut = pos_y_piece_dans_plateau - 1;
            int pos_y_bloc_bas = pos_y_piece_dans_plateau + 1;
            int pos_x_bloc_gauche = pos_x_piece_dans_plateau - 1;
            int pos_x_bloc_droite = pos_x_piece_dans_plateau + 1;

            // Bloc haut-gauche
            if (pos_x_bloc_gauche > 0 && pos_y_bloc_haut > 0)
            {
                t_bloc *bloc_haut_gauche = plateau->damier[pos_y_bloc_haut][pos_x_bloc_gauche];
                if (bloc_haut_gauche && bloc_haut_gauche->piece->couleur == piece->couleur)
                {
                    return 1;
                }
            }

            // Bloc haut-droite
            if (pos_x_bloc_droite < NB_COLONNES && pos_y_bloc_haut > 0)
            {
                t_bloc *bloc_haut_droite = plateau->damier[pos_y_bloc_haut][pos_x_bloc_droite];
                if (bloc_haut_droite && bloc_haut_droite->piece->couleur == piece->couleur)
                {
                    return 1;
                }
            }

            // Bloc bas-gauche
            if (pos_x_bloc_gauche > 0 && pos_y_bloc_bas < NB_LIGNES)
            {
                t_bloc *bloc_bas_gauche = plateau->damier[pos_y_bloc_bas][pos_x_bloc_gauche];
                if (bloc_bas_gauche && bloc_bas_gauche->piece->couleur == piece->couleur)
                {
                    return 1;
                }
            }

            // Bloc bas-droite
            if (pos_x_bloc_droite < NB_COLONNES && pos_y_bloc_bas < NB_LIGNES)
            {
                t_bloc *bloc_haut_droite = plateau->damier[pos_y_bloc_bas][pos_x_bloc_droite];
                if (bloc_haut_droite && bloc_haut_droite->piece->couleur == piece->couleur)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void poser_piece(t_plateau *plateau, t_piece *piece, int pos_x, int pos_y)
{
    int i;
    for (i = 0; i < piece->nb_blocs; i++)
    {
        int pos_x_piece_dans_plateau = piece->blocs[i].x + pos_x;
        int pos_y_piece_dans_plateau = piece->blocs[i].y + pos_y;
        plateau->damier[pos_y_piece_dans_plateau][pos_x_piece_dans_plateau] = &piece->blocs[i];
    }
}

void afficher_plateau(t_plateau *plateau)
{
    printf("   ");

    char lettre;
    for (lettre = 'A'; lettre <= 'T'; lettre++)
    {
        printf("%c ", lettre);
    }

    int ligne;
    for (ligne = 0; ligne < NB_LIGNES; ligne++)
    {
        printf("\n%2d", ligne + 1);

        int colonne;
        for (colonne = 0; colonne < NB_COLONNES; colonne++)
        {
            printf("|");
            t_bloc *bloc_courant = plateau->damier[ligne][colonne];
            if (bloc_courant)
            {
                 printf("%c", bloc_courant->piece->symbole);
            }
            else
            {
                printf(" ");
            }
        }
        printf("|");
    }
}
