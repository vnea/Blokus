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

int main()
{
    // Création pieces
    t_piece pieces[NB_PIECES_MAX];
    charger_pieces(pieces);

    // Création joueurs
    t_joueur joueurs[4];
    initialiser_joueur(&joueurs[0], "J1", pieces, COULEUR_BLEU);
    initialiser_joueur(&joueurs[1], "J2", pieces, COULEUR_ROUGE);
    //initialiser_joueur(&joueurs[2], "J3", pieces, COULEUR_JAUNE);
    //initialiser_joueur(&joueurs[3], "J4", pieces, COULEUR_VERT);

    // Création plateau
    t_plateau plateau;
    initialiser_plateau(&plateau);

    //afficher_pieces_joueur(&joueurs[1]);

    //afficher_pieces_joueur(&joueurs[2]);
    //afficher_pieces_joueur(&joueurs[3]);

    int tour = 0;
    int fin_jeu = 0;
    do
    {
        t_joueur *joueur_courant = &joueurs[tour % 2];

        gotoxy(0, 0);
        afficher_plateau(&plateau);
        printf("\n");
        afficher_pieces_joueur(joueur_courant);
        printf("\n");
        afficher_piece_selectionnee_joueur(joueur_courant);

        printf("\n%s, a vous de jouer !\n", joueur_courant->pseudo);
        printf("Choisissez la piece a poser : ");
        char piece;
        scanf("%c", &piece);
        getchar();
        piece = toupper(piece);

        joueur_courant->piece_selectionnee = &joueur_courant->pieces[piece - 'A'];
        poser_piece_dans_plateau_piece_selectionne(joueur_courant, joueur_courant->piece_selectionnee);
        gotoxy(0, 37);
        afficher_piece_selectionnee_joueur(joueur_courant);


        printf("\nRotation / Inversion (touches G-D-I) : ");
        char mouvement[BUFFER];
        fgets(mouvement, BUFFER, stdin);
        int i;
        for (i = 0; i < strlen(mouvement); i++)
        {

        }

        printf("\nPositionnez la piece dans la grille (ex : A 15): ");
        t_coord pos_piece_dans_plateau;
        char lettre_col;
        scanf(" %c", &lettre_col);
        pos_piece_dans_plateau.x = lettre_col - 'A';

        scanf(" %d", &pos_piece_dans_plateau.y);
        getchar();
        pos_piece_dans_plateau.y--;

        if (peut_poser_piece_dans_plateau(&plateau, joueur_courant->piece_selectionnee, &pos_piece_dans_plateau, joueur_courant->premier_coup))
        {
            poser_piece(&plateau, joueur_courant->piece_selectionnee, &pos_piece_dans_plateau);
            joueur_courant->premier_coup = 0;
            joueur_courant->piece_deja_posee[piece - 'A'] = 1;
            joueur_courant->piece_selectionnee = NULL;
        }

        tour++;
    } while (!fin_jeu);

    /*
    t_coord coord1 = {0, 0};
    if (peut_poser_piece_dans_plateau(&plateau, &pieces[0], &coord1, 1))
    {
        poser_piece(&plateau, &pieces[0], &coord1);
    }


    printf("\n");
    afficher_plateau(&plateau);


    t_coord coord2 = {NB_COLONNES  - 1, 0};
    if (peut_poser_piece_dans_plateau(&plateau, &pieces['G' - 'A'], &coord2, 1))
    {
        poser_piece(&plateau, &pieces['G' - 'A'], &coord2);
    }

    printf("\n");
    afficher_plateau(&plateau);
    */

    return 0;
}
