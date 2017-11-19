#include<conio.h>
#include<ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../include/console.h"
#include "../include/plateau.h"
#include "../include/piece.h"
#include "../include/bloc.h"
#include "../include/affichage.h"
#include "../include/joueur.h"

#define BUFFER 64

void effacer_instructions();

int main()
{
    // Création pieces
    t_piece pieces[NB_PIECES_MAX];
    charger_pieces(pieces);

    // Création joueurs
    t_joueur joueurs[4];
    initialiser_joueur(&joueurs[0], "J1", pieces, COULEUR_BLEU);
    initialiser_joueur(&joueurs[1], "J2", pieces, COULEUR_ROUGE);
    initialiser_joueur(&joueurs[2], "J3", pieces, COULEUR_JAUNE);
    initialiser_joueur(&joueurs[3], "J4", pieces, COULEUR_VERT);

    // Création plateau
    t_plateau plateau;
    initialiser_plateau(&plateau);

    int tour = 0;
    int fin_jeu = 0;
    do
    {
        t_joueur *joueur_courant = &joueurs[tour % 4];

        afficher_plateau(&plateau);
        printf("\n");
        afficher_pieces_joueur(joueur_courant);
        printf("\n");
        afficher_piece_selectionnee_joueur(joueur_courant);

        char piece;
        SELECTION_PIECE:
        do
        {
            effacer_instructions();
            printf("\n%s, a vous de jouer !\n", joueur_courant->pseudo);
            printf("Choisissez la piece a poser : ");
            scanf("%c", &piece);
        } while (piece < 'A' || piece > 'U' || joueur_courant->piece_deja_posee[piece - 'A']);

        t_piece *piece_originale = &joueur_courant->pieces[piece - 'A'];
        copier_piece(piece_originale, &joueur_courant->piece_selectionnee);
        joueur_courant->piece_a_ete_selectionnee = 1;

        afficher_piece_selectionnee_joueur(joueur_courant);

        SELECTION_ROTATION_INVERSION:
        effacer_instructions();

        printf("\nRotation / Inversion (touches G-D-I et * pour retour) : ");
        char mouvement[BUFFER];
        fflush(stdin);
        fgets(mouvement, BUFFER, stdin);
        int i;
        for (i = 0; i < strlen(mouvement); i++)
        {
            if (mouvement[i] == 'G')
            {
                rotation_gauche_piece(piece_originale);
                rotation_gauche_piece(&joueur_courant->piece_selectionnee);
            }
            else if (mouvement[i] == 'D')
            {
                rotation_droite_piece(piece_originale);
                rotation_droite_piece(&joueur_courant->piece_selectionnee);
            }
            else if (mouvement[i] == 'I')
            {
                inverser_piece(piece_originale);
                inverser_piece(&joueur_courant->piece_selectionnee);
            }
            else if (mouvement[i] == '*')
            {
                afficher_piece_selectionnee_joueur(joueur_courant);
                goto SELECTION_PIECE;
            }
        }

        afficher_piece_selectionnee_joueur(joueur_courant);

        int peut_poser_piece;
        t_coord pos_piece_dans_plateau;
        do
        {
            effacer_instructions();

            printf("\nPositionnez la piece dans la grille (ex : A 15), touche * pour retour: ");
            char lettre_col;
            scanf(" %c", &lettre_col);
            if (lettre_col == '*')
            {
                goto SELECTION_ROTATION_INVERSION;
            }

            pos_piece_dans_plateau.x = lettre_col - 'A';

            scanf(" %d", &pos_piece_dans_plateau.y);
            getchar();
            pos_piece_dans_plateau.y--;
            peut_poser_piece = peut_poser_piece_dans_plateau(&plateau, &joueur_courant->piece_selectionnee, &pos_piece_dans_plateau, joueur_courant->premier_coup);
        } while (!peut_poser_piece);

        poser_piece_dans_plateau(&plateau, piece_originale, &pos_piece_dans_plateau);
        joueur_courant->premier_coup = 0;
        joueur_courant->piece_deja_posee[piece - 'A'] = 1;

        joueur_courant->piece_a_ete_selectionnee = 0;
        tour++;
    } while (!fin_jeu);

    return 0;
}

void effacer_instructions()
{
    gotoxy(0, 28);
    int i;
    for (i = 0 ; i < 1000; i++)
    {
        printf(" ");
    }
    gotoxy(0, 28);
}
