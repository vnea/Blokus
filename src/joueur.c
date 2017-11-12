#include <stdio.h>
#include <string.h>

#include "../include/affichage.h"
#include "../include/joueur.h"

void initialiser_joueur(t_joueur *joueur, char pseudo[TAILLE_PSEUDO_MAX], t_piece pieces[NB_PIECES_MAX], int couleur_pieces)
{
    strcpy(joueur->pseudo, pseudo);
    joueur->premier_coup = 1;

    int i;
    for (i = 0; i < NB_PIECES_MAX; i++)
    {
        joueur->piece_deja_posee[i] = 0;

        t_piece *piece_courante = &joueur->pieces[i];
        piece_courante->symbole = pieces[i].symbole;
        piece_courante->couleur = couleur_pieces;
        int j;
        for (j = 0; j < pieces[i].nb_blocs; j++)
        {
            piece_courante->blocs[j].coord = pieces[i].blocs[j].coord;
            piece_courante->blocs[j].est_un_angle = pieces[i].blocs[j].est_un_angle;
            piece_courante->blocs[j].piece = piece_courante;
        }
        piece_courante->nb_blocs = pieces[i].nb_blocs;
    }

    poser_toutes_les_pieces_dans_plateau_selection_piece(joueur);
}

void poser_piece_dans_plateau_selection_piece(t_joueur *joueur, t_piece *piece, t_coord *coord)
{
    int i;
    for (i = 0; i < piece->nb_blocs; i++)
    {
        t_coord coord_piece_dans_plateau_selection_piece =
        {
            piece->blocs[i].coord.x + coord->x,
            piece->blocs[i].coord.y + coord->y
        };
        joueur->plateau_selection_piece[coord_piece_dans_plateau_selection_piece.y][coord_piece_dans_plateau_selection_piece.x] = piece->blocs[i];
    }
}

void poser_toutes_les_pieces_dans_plateau_selection_piece(t_joueur *joueur)
{
    // On met des blocs "vides"
    int i;
    for (i = 0; i < NB_LIGNES_PLATEAU_JOUEUR; i++)
    {
        int j;
        for (j = 0; j < NB_COLONNES_PLATEAU_JOUEUR; j++)
        {
            t_bloc bloc;
            bloc.piece = NULL;
            joueur->plateau_selection_piece[i][j] = bloc;
        }
    }

    // On place les pieces
    t_coord pos_piece_A = {0, 0};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['A' - 'A'], &pos_piece_A);

    t_coord pos_piece_B = {2, 0};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['B' - 'A'], &pos_piece_B);

    t_coord pos_piece_C = {5, 0};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['C' - 'A'], &pos_piece_C);

    t_coord pos_piece_D = {9, 0};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['D' - 'A'], &pos_piece_D);

    t_coord pos_piece_E = {12, 0};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['E' - 'A'], &pos_piece_E);

    t_coord pos_piece_F = {18, 0};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['F' - 'A'], &pos_piece_F);

    t_coord pos_piece_G = {0, 2};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['G' - 'A'], &pos_piece_G);

    t_coord pos_piece_H = {3, 2};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['H' - 'A'], &pos_piece_H);

    t_coord pos_piece_I = {6, 2};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['I' - 'A'], &pos_piece_I);

    t_coord pos_piece_J = {10, 3};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['J' - 'A'], &pos_piece_J);

    t_coord pos_piece_K = {14, 2};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['K' - 'A'], &pos_piece_K);

    t_coord pos_piece_L = {0, 6};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['L' - 'A'], &pos_piece_L);

    t_coord pos_piece_M = {6, 5};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['M' - 'A'], &pos_piece_M);

    t_coord pos_piece_N = {9, 5};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['N' - 'A'], &pos_piece_N);

    t_coord pos_piece_O = {13, 6};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['O' - 'A'], &pos_piece_O);

    t_coord pos_piece_P = {16, 6};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['P' - 'A'], &pos_piece_P);

    t_coord pos_piece_Q = {0, 8};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['Q' - 'A'], &pos_piece_Q);

    t_coord pos_piece_R = {3, 9};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['R' - 'A'], &pos_piece_R);

    t_coord pos_piece_S = {7, 9};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['S' - 'A'], &pos_piece_S);

    t_coord pos_piece_T = {10, 9};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['T' - 'A'], &pos_piece_T);

    t_coord pos_piece_U = {16, 9};
    poser_piece_dans_plateau_selection_piece(joueur, &joueur->pieces['U' - 'A'], &pos_piece_U);
}

void afficher_pieces_joueur(t_joueur *joueur)
{
    int ligne;
    for (ligne = 0; ligne < NB_LIGNES_PLATEAU_JOUEUR; ligne++)
    {
        int colonne;
        for (colonne = 0; colonne < NB_COLONNES_PLATEAU_JOUEUR; colonne++)
        {
            printf("|");
            t_bloc *bloc_courant = &joueur->plateau_selection_piece[ligne][colonne];
            if (bloc_courant->piece)
            {
                t_piece *piece_du_bloc = bloc_courant->piece;
                if (joueur->piece_deja_posee[piece_du_bloc->symbole - 'A'])
                {
                    print_char_couleur(bloc_courant->piece->symbole, COULEUR_GRIS);
                }
                else
                {
                    print_char_couleur(bloc_courant->piece->symbole, piece_du_bloc->couleur);
                }
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
}
