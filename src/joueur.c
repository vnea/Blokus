#include <stdio.h>
#include <string.h>

#include "../include/affichage.h"
#include "../include/joueur.h"

void initialiser_joueur(t_joueur *joueur, char pseudo[BUFFER], t_piece pieces[NB_PIECES_MAX], int couleur_pieces, int est_ia)
{
    strcpy(joueur->pseudo, pseudo);
    joueur->premier_coup = 1;
    joueur->peut_jouer = 1;
    joueur->couleur_pieces = couleur_pieces;
    joueur->est_ia = est_ia;

    // Copies des pieces
    int num_piece;
    for (num_piece = 0; num_piece < NB_PIECES_MAX; num_piece++)
    {
        joueur->piece_deja_posee[num_piece] = 0;
        copier_piece(&pieces[num_piece], &joueur->pieces[num_piece]);
        joueur->pieces[num_piece].couleur = couleur_pieces;
    }

    initialiser_plateau_selection_pieces(joueur);

    initialiser_plateau_piece_selectionnee(joueur);
    joueur->piece_selectionnee = NULL;
}

int peut_jouer_joueur(t_joueur *joueur, t_plateau *plateau)
{
    // Pas besoin de refaire le calcul si le joueur a deja perdu
    if (!joueur->peut_jouer)
    {
        return 0;
    }

    int num_piece;
    for (num_piece = 0; num_piece < NB_PIECES_MAX; num_piece++)
    {
        if (!joueur->piece_deja_posee[num_piece])
        {
            int ligne;
            for (ligne = 0; ligne < NB_LIGNES_PLATEAU; ligne++)
            {
                int colonne;
                for (colonne = 0; colonne < NB_COLONNES_PLATEAU; colonne++)
                {
                    // On travaille sur une copie de la piece pour ne pas toucher aux coord de l'originale
                    t_piece copie_piece;
                    copier_piece(&joueur->pieces[num_piece], &copie_piece);
                    t_coord pos_piece_dans_plateau = {colonne, ligne};

                    // Cas normal
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        return 1;
                    }

                    // Inversion
                    inverser_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        return 1;
                    }

                    // 1 rotation droite avec inversion
                    rotation_droite_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        return 1;
                    }

                    // 1 rotation droite normale
                    inverser_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        return 1;
                    }

                    // 2 rotations droites normales
                    rotation_droite_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        return 1;
                    }

                    // 2 rotations droites normales avec inversion
                    inverser_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        return 1;
                    }

                    // 3 rotations droites avec inversion
                    rotation_droite_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        return 1;
                    }

                    // 3 rotations droites normales
                    inverser_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        return 1;
                    }
                }
            }
        }
    }

    joueur->peut_jouer = 0;
    return joueur->peut_jouer;
}

int nb_pieces_restantes_joueur(t_joueur *joueur)
{
    int nb_pieces_restantes = NB_PIECES_MAX;
    int num_piece;
    for (num_piece = 0; num_piece < NB_PIECES_MAX; num_piece++)
    {
        if (joueur->piece_deja_posee[num_piece])
        {
            nb_pieces_restantes--;
        }
    }

    return nb_pieces_restantes;
}

void choisir_coup_ia(t_joueur *joueur, t_plateau *plateau, int *indice_piece, t_coord *pos_piece)
{
    int num_piece;
    for (num_piece = 0; num_piece < NB_PIECES_MAX; num_piece++)
    {
        if (!joueur->piece_deja_posee[num_piece])
        {
            int ligne;
            for (ligne = 0; ligne < NB_LIGNES_PLATEAU; ligne++)
            {
                int colonne;
                for (colonne = 0; colonne < NB_COLONNES_PLATEAU; colonne++)
                {
                    // On travaille sur une copie de la piece pour ne pas toucher aux coord de l'originale
                    t_piece copie_piece;
                    copier_piece(&joueur->pieces[num_piece], &copie_piece);
                    t_coord pos_piece_dans_plateau = {colonne, ligne};

                    // Cas normal
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        *indice_piece = num_piece;
                        pos_piece->x = pos_piece_dans_plateau.x;
                        pos_piece->y = pos_piece_dans_plateau.y;
                        joueur->piece_selectionnee = &joueur->pieces[num_piece];
                        return;
                    }

                    // Inversion
                    inverser_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        *indice_piece = num_piece;
                        pos_piece->x = pos_piece_dans_plateau.x;
                        pos_piece->y = pos_piece_dans_plateau.y;
                        joueur->piece_selectionnee = &joueur->pieces[num_piece];
                        inverser_piece(joueur->piece_selectionnee);
                        return;
                    }

                    // 1 rotation droite avec inversion
                    rotation_droite_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        *indice_piece = num_piece;
                        pos_piece->x = pos_piece_dans_plateau.x;
                        pos_piece->y = pos_piece_dans_plateau.y;
                        joueur->piece_selectionnee = &joueur->pieces[num_piece];
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        return;
                    }

                    // 1 rotation droite normale
                    inverser_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        *indice_piece = num_piece;
                        pos_piece->x = pos_piece_dans_plateau.x;
                        pos_piece->y = pos_piece_dans_plateau.y;
                        joueur->piece_selectionnee = &joueur->pieces[num_piece];
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        return;
                    }

                    // 2 rotations droites normales
                    rotation_droite_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        *indice_piece = num_piece;
                        pos_piece->x = pos_piece_dans_plateau.x;
                        pos_piece->y = pos_piece_dans_plateau.y;
                        joueur->piece_selectionnee = &joueur->pieces[num_piece];
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        return;
                    }

                    // 2 rotations droites normales avec inversion
                    inverser_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        *indice_piece = num_piece;
                        pos_piece->x = pos_piece_dans_plateau.x;
                        pos_piece->y = pos_piece_dans_plateau.y;
                        joueur->piece_selectionnee = &joueur->pieces[num_piece];
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        return;
                    }

                    // 3 rotations droites avec inversion
                    rotation_droite_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        *indice_piece = num_piece;
                        pos_piece->x = pos_piece_dans_plateau.x;
                        pos_piece->y = pos_piece_dans_plateau.y;
                        joueur->piece_selectionnee = &joueur->pieces[num_piece];
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        return;
                    }

                    // 3 rotations droites normales
                    inverser_piece(&copie_piece);
                    if (peut_poser_piece_dans_plateau(plateau, &copie_piece, &pos_piece_dans_plateau, joueur->premier_coup))
                    {
                        *indice_piece = num_piece;
                        pos_piece->x = pos_piece_dans_plateau.x;
                        pos_piece->y = pos_piece_dans_plateau.y;
                        joueur->piece_selectionnee = &joueur->pieces[num_piece];
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        rotation_droite_piece(joueur->piece_selectionnee);
                        inverser_piece(joueur->piece_selectionnee);
                        return;
                    }
                }
            }
        }
    }
}

void initialiser_plateau_selection_pieces(t_joueur *joueur)
{
    // On met des blocs "vides"
    int ligne;
    for (ligne = 0; ligne < NB_LIGNES_PLATEAU_JOUEUR; ligne++)
    {
        int colonne;
        for (colonne = 0; colonne < NB_COLONNES_PLATEAU_JOUEUR; colonne++)
        {
            joueur->plateau_selection_pieces[ligne][colonne] = NULL;
        }
    }

    // On place les pieces
    t_coord pos_piece_A = {0, 0};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['A' - 'A'], &pos_piece_A);

    t_coord pos_piece_B = {2, 0};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['B' - 'A'], &pos_piece_B);

    t_coord pos_piece_C = {5, 0};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['C' - 'A'], &pos_piece_C);

    t_coord pos_piece_D = {9, 0};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['D' - 'A'], &pos_piece_D);

    t_coord pos_piece_E = {12, 0};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['E' - 'A'], &pos_piece_E);

    t_coord pos_piece_F = {18, 0};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['F' - 'A'], &pos_piece_F);

    t_coord pos_piece_G = {0, 2};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['G' - 'A'], &pos_piece_G);

    t_coord pos_piece_H = {3, 2};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['H' - 'A'], &pos_piece_H);

    t_coord pos_piece_I = {6, 2};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['I' - 'A'], &pos_piece_I);

    t_coord pos_piece_J = {10, 3};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['J' - 'A'], &pos_piece_J);

    t_coord pos_piece_K = {14, 2};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['K' - 'A'], &pos_piece_K);

    t_coord pos_piece_L = {0, 6};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['L' - 'A'], &pos_piece_L);

    t_coord pos_piece_M = {6, 5};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['M' - 'A'], &pos_piece_M);

    t_coord pos_piece_N = {9, 5};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['N' - 'A'], &pos_piece_N);

    t_coord pos_piece_O = {13, 6};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['O' - 'A'], &pos_piece_O);

    t_coord pos_piece_P = {16, 6};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['P' - 'A'], &pos_piece_P);

    t_coord pos_piece_Q = {0, 8};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['Q' - 'A'], &pos_piece_Q);

    t_coord pos_piece_R = {3, 9};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['R' - 'A'], &pos_piece_R);

    t_coord pos_piece_S = {7, 9};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['S' - 'A'], &pos_piece_S);

    t_coord pos_piece_T = {10, 9};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['T' - 'A'], &pos_piece_T);

    t_coord pos_piece_U = {16, 9};
    poser_piece_dans_plateau_selection_pieces(joueur, &joueur->pieces['U' - 'A'], &pos_piece_U);
}

void poser_piece_dans_plateau_selection_pieces(t_joueur *joueur, t_piece *piece, t_coord *coord)
{
    t_bloc *bloc_plus_haut_gauche = trouver_bloc_plus_haut_gauche_piece(piece);

    int num_bloc;
    for (num_bloc = 0; num_bloc < piece->nb_blocs; num_bloc++)
    {
        t_coord coord_piece_dans_plateau_selection_pieces =
        {
            piece->blocs[num_bloc].coord.x - bloc_plus_haut_gauche->coord.x + coord->x,
            piece->blocs[num_bloc].coord.y - bloc_plus_haut_gauche->coord.y + coord->y
        };
        joueur->plateau_selection_pieces[coord_piece_dans_plateau_selection_pieces.y][coord_piece_dans_plateau_selection_pieces.x] = &piece->blocs[num_bloc];
    }
}

void afficher_pieces_joueur(t_joueur *joueur)
{
    int ligne;
    for (ligne = 0; ligne < NB_LIGNES_PLATEAU_JOUEUR; ligne++)
    {
        gotoligcol(ligne + 2, 50);
        int colonne;
        for (colonne = 0; colonne < NB_COLONNES_PLATEAU_JOUEUR; colonne++)
        {
            printf("|");
            t_bloc *bloc_courant = joueur->plateau_selection_pieces[ligne][colonne];
            if (bloc_courant)
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
        printf("|\n\n");
    }
}

void initialiser_plateau_piece_selectionnee(t_joueur *joueur)
{
    int ligne;
    for (ligne = 0; ligne < NB_BLOCS_MAX; ligne++)
    {
        int colonne;
        for (colonne = 0; colonne < NB_BLOCS_MAX; colonne++)
        {
            joueur->plateau_piece_selectionnee[ligne][colonne] = NULL;
        }
    }
}

int peut_poser_piece_dans_plateau_piece_selectionnee(t_joueur *joueur, t_piece *piece, t_coord *pos_piece)
{
    t_bloc *bloc_plus_haut_gauche = trouver_bloc_plus_haut_gauche_piece(piece);

    int num_bloc;
    for (num_bloc = 0; num_bloc < piece->nb_blocs; num_bloc++)
    {
        t_coord coord_piece_dans_plateau_piece_selectionnee =
        {
            piece->blocs[num_bloc].coord.x - bloc_plus_haut_gauche->coord.x + pos_piece->x,
            piece->blocs[num_bloc].coord.y - bloc_plus_haut_gauche->coord.y + pos_piece->y
        };

        // Verifier si le bloc est bien dans le plateau
        if (coord_piece_dans_plateau_piece_selectionnee.x < 0 || coord_piece_dans_plateau_piece_selectionnee.x >= NB_BLOCS_MAX ||
            coord_piece_dans_plateau_piece_selectionnee.y < 0 || coord_piece_dans_plateau_piece_selectionnee.y >= NB_BLOCS_MAX)
        {
           return 0;
        }
    }

    return 1;
}

void poser_piece_dans_plateau_piece_selectionnee(t_joueur *joueur, t_piece *piece, t_coord *pos_piece)
{
    initialiser_plateau_piece_selectionnee(joueur);
    t_bloc *bloc_plus_haut_gauche = trouver_bloc_plus_haut_gauche_piece(piece);

    int num_bloc;
    for (num_bloc = 0; num_bloc < piece->nb_blocs; num_bloc++)
    {
        t_coord coord_piece_dans_plateau_piece_selectionnee =
        {
            piece->blocs[num_bloc].coord.x - bloc_plus_haut_gauche->coord.x + pos_piece->x,
            piece->blocs[num_bloc].coord.y - bloc_plus_haut_gauche->coord.y + pos_piece->y
        };
        joueur->plateau_piece_selectionnee[coord_piece_dans_plateau_piece_selectionnee.y][coord_piece_dans_plateau_piece_selectionnee.x] = &piece->blocs[num_bloc];
    }
}

void afficher_piece_selectionnee_joueur(t_joueur *joueur)
{
    if (joueur->piece_selectionnee)
    {
        int peut_poser = 0;
        int ligne;
        for (ligne = 0; !peut_poser && ligne < NB_BLOCS_MAX; ligne++)
        {
            int colonne;
            for (colonne = 0; !peut_poser && colonne < NB_BLOCS_MAX; colonne++)
            {
                t_coord delta = {colonne, ligne};
                peut_poser = peut_poser_piece_dans_plateau_piece_selectionnee(joueur, joueur->piece_selectionnee, &delta);
                if (peut_poser)
                {
                    poser_piece_dans_plateau_piece_selectionnee(joueur, joueur->piece_selectionnee, &delta);
                }
            }
        }
    }

    int ligne;
    for (ligne = 0; ligne < NB_BLOCS_MAX; ligne++)
    {
        gotoligcol(ligne + 16, 50);
        int colonne;
        for (colonne = 0; colonne < NB_BLOCS_MAX; colonne++)
        {
            printf("|");
            t_bloc *bloc_courant = joueur->plateau_piece_selectionnee[ligne][colonne];
            if (joueur->piece_selectionnee && bloc_courant)
            {
                print_char_couleur(bloc_courant->piece->symbole, bloc_courant->piece->couleur);
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
}
