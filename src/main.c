#include<ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../include/console.h"
#include "../include/plateau.h"
#include "../include/piece.h"
#include "../include/bloc.h"
#include "../include/affichage.h"
#include "../include/joueur.h"

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

        system("cls");
        afficher_plateau(&plateau);
        printf("\n");
        afficher_pieces_joueur(joueur_courant);

        printf("\n%s, a vous de jouer !\n", joueur_courant->pseudo);
        printf("Choisissez la piece a poser : ");
        char piece;
        scanf(" %c", &piece);
        piece = toupper(piece);

        t_piece *piece_selectionnee = &joueur_courant->pieces[piece - 'A'];
/*
        printf("\nRotation / Inversion (touches G-D-I) : ");
        char mouvement;
        scanf(" %c", &mouvement);
        mouvement = toupper(mouvement);
*/

        printf("\nPositionnez la piece dans la grille (ex : A 15): ");
        t_coord pos_piece_dans_plateau;
        scanf(" %c", &pos_piece_dans_plateau.x);
        pos_piece_dans_plateau.x -= 'A';

        scanf(" %d", &pos_piece_dans_plateau.y);
        pos_piece_dans_plateau.y--;

        if (peut_poser_piece_dans_plateau(&plateau, piece_selectionnee, &pos_piece_dans_plateau, joueur_courant->premier_coup))
        {
            poser_piece(&plateau, piece_selectionnee, &pos_piece_dans_plateau);
            joueur_courant->premier_coup = 0;
            joueur_courant->piece_deja_posee[piece - 'A'] = 1;
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
