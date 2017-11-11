#include<ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
    t_joueur joueurs[2];
    initialiser_joueur(&joueurs[0], "J1", pieces, 1);
    initialiser_joueur(&joueurs[1], "J2", pieces, 2);

    // Création plateau
    t_plateau plateau;
    initialiser_plateau(&plateau);

    int tour = 0;
    int fin_jeu = 0;
    do
    {
        afficher_plateau(&plateau);

        t_joueur *joueur_courant = &joueurs[tour % 2];
        printf("\n%s, a vous de jouer !\n", joueur_courant->pseudo);
        printf("Choisissez la piece a poser : ");
        char piece;
        scanf(" %c", &piece);
        piece = toupper(piece);

        printf("\nRotation / Inversion (touches G-D-I) : ");
        char mouvement;
        scanf(" %c", &mouvement);
        mouvement = toupper(mouvement);


        tour++;
    } while (!fin_jeu);


    /*afficher_piece(&pieces[5]);
    rotation_gauche_piece(&pieces[5]);

        afficher_piece(&pieces[5]);
*/


/*
    t_coord coord1 = {0, 0};
    if (peut_poser_piece_dans_plateau(&plateau, &pieces[0], &coord1, 1))
    {
        poser_piece(&plateau, &pieces[0], &coord1);
    }


    printf("\n");
    afficher_plateau(&plateau);
*/
/*
    t_coord coord2 = {NB_COLONNES  - 3, 0};
    if (peut_poser_piece_dans_plateau(&plateau, &pieces[2], &coord2, 1))
    {
        poser_piece(&plateau, &pieces[2], &coord2);
    }

    printf("\n");
    afficher_plateau(&plateau);
/*
    if (peut_poser_piece_dans_plateau(&plateau, &pieces[1], 0, 1))
    {
        poser_piece(&plateau, &pieces[1], 0, 1);
    }
    printf("\n");
    afficher_plateau(&plateau);
*/
    return 0;
}
