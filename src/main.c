#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../include/affichage.h"
#include "../include/joueur.h"
#include "../include/piece.h"
#include "../include/plateau.h"

#define NB_JOUEURS_MAX 4
#define BUFFER 100

void effacer_instructions();
void afficher_liste_joueurs(t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs, t_plateau *plateau, t_joueur *joueur_courant);
void afficher_fin_partie(t_plateau *plateau, t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs);
t_joueur *selectionner_joueur_suivant(t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs, t_joueur *joueur_courant, t_plateau *plateau, int *num_joueur);

int main()
{
    printf("Veuillez maximiser la fenetre pour avoir une meilleure experience de jeu.\n\n");

    // Creation pieces
    t_piece pieces[NB_PIECES_MAX];
    charger_pieces(pieces);

    // Creation des joueurs
    int nb_joueurs;
    do
    {
        printf("Nombre de joueurs (entre 2 et %d joueurs) : ", NB_JOUEURS_MAX);
        scanf(" %d", &nb_joueurs);
    }
    while (nb_joueurs < 2 || nb_joueurs > NB_JOUEURS_MAX);

    t_joueur joueurs[NB_JOUEURS_MAX];
    int couleurs_joueurs[NB_JOUEURS_MAX] =
    {
        COULEUR_BLEU,
        COULEUR_ROUGE,
        COULEUR_JAUNE,
        COULEUR_VERT
    };
    int num_joueur;
    for (num_joueur = 0; num_joueur < nb_joueurs; num_joueur++)
    {
        char response_est_ia;
        do
        {
            printf("IA (O pour oui, N pour non) : ");
            scanf(" %c", &response_est_ia);
        }
        while (response_est_ia != 'O' && response_est_ia != 'o' &&response_est_ia != 'N' && response_est_ia !='n');

        int est_ia = response_est_ia == 'O' || response_est_ia == 'o';
        // Pseudo du joueur
        char pseudo[BUFFER];
        do
        {
            if (est_ia)
            {
                printf("Pseudo de l'ordinateur : ");
            }
            else
            {
                printf("Pseudo du joueur : ");
            }
            fflush(stdin);
            fgets(pseudo, BUFFER, stdin);
        }
        while (strlen(pseudo) == 1);

        pseudo[strlen(pseudo) - 1] = '\0';
        initialiser_joueur(&joueurs[num_joueur], pseudo, pieces, couleurs_joueurs[num_joueur], est_ia);
        printf("\n");
    }

    // Création plateau
    t_plateau plateau;
    initialiser_plateau(&plateau);

    num_joueur = 0;
    int fin_jeu = 0;
    t_joueur *joueur_courant = &joueurs[0];
    system("cls");
    do
    {
        afficher_plateau(&plateau);
        afficher_pieces_joueur(joueur_courant);

        t_coord pos_piece_dans_plateau;
        int indice_piece;

        if (joueur_courant->est_ia)
        {
            effacer_instructions();
            afficher_liste_joueurs(joueurs, nb_joueurs, &plateau, joueur_courant);
            afficher_piece_selectionnee_joueur(joueur_courant);

            choisir_coup_ia(joueur_courant, &plateau, &indice_piece, &pos_piece_dans_plateau);
            Sleep(TEMP_REFLEXION_IA);

            afficher_piece_selectionnee_joueur(joueur_courant);
            Sleep(100);
        }
        else
        {
            // Selectionner piece
            char piece;
SELECTION_PIECE:
            joueur_courant->piece_selectionnee = NULL;
            afficher_piece_selectionnee_joueur(joueur_courant);
            do
            {
                effacer_instructions();
                afficher_liste_joueurs(joueurs, nb_joueurs, &plateau, joueur_courant);
                printf("Choisissez la piece a poser : ");
                scanf("%c", &piece);
                indice_piece = piece - 'A';
            }
            while (piece < 'A' || piece > 'U' || joueur_courant->piece_deja_posee[indice_piece]);
            joueur_courant->piece_selectionnee = &joueur_courant->pieces[indice_piece];
            afficher_piece_selectionnee_joueur(joueur_courant);

            // Selectionner les rotations/inversions
SELECTION_ROTATION_INVERSION:
            effacer_instructions();
            afficher_liste_joueurs(joueurs, nb_joueurs, &plateau, joueur_courant);
            printf("Rotation / Inversion (touches G-D-I, Entree pour ne rien faire ou * pour retour) : ");

            char transformations[BUFFER];
            fflush(stdin);
            fgets(transformations, BUFFER, stdin);
            int i;
            for (i = 0; i < strlen(transformations); i++)
            {
                if (transformations[i] == 'G')
                {
                    rotation_gauche_piece(joueur_courant->piece_selectionnee);
                }
                else if (transformations[i] == 'D')
                {
                    rotation_droite_piece(joueur_courant->piece_selectionnee);
                }
                else if (transformations[i] == 'I')
                {
                    inverser_piece(joueur_courant->piece_selectionnee);
                }
                else if (transformations[i] == '*')
                {
                    goto SELECTION_PIECE;
                }
            }
            afficher_piece_selectionnee_joueur(joueur_courant);

            // Selectionner position de la piece
            do
            {
                effacer_instructions();
                afficher_liste_joueurs(joueurs, nb_joueurs, &plateau, joueur_courant);
                printf("Positionnez la piece dans la grille (ex : A 1), touche * pour retour: ");

                // Demande de la colonne
                char lettre_col;
                scanf(" %c", &lettre_col);
                if (lettre_col == '*')
                {
                    goto SELECTION_ROTATION_INVERSION;
                }

                // Demande de la ligne
                scanf(" %d", &pos_piece_dans_plateau.y);

                pos_piece_dans_plateau.x = lettre_col - 'A';
                pos_piece_dans_plateau.y--;
            }
            while (!peut_poser_piece_dans_plateau(&plateau, joueur_courant->piece_selectionnee, &pos_piece_dans_plateau, joueur_courant->premier_coup));
        }

        poser_piece_dans_plateau(&plateau, joueur_courant->piece_selectionnee, &pos_piece_dans_plateau);
        joueur_courant->premier_coup = 0;
        joueur_courant->piece_deja_posee[indice_piece] = 1;
        joueur_courant->piece_selectionnee = NULL;

        fin_jeu = nb_pieces_restantes_joueur(joueur_courant) == 0;
        if (!fin_jeu)
        {
            joueur_courant = selectionner_joueur_suivant(joueurs, nb_joueurs, joueur_courant, &plateau, &num_joueur);
            fin_jeu = joueur_courant == NULL;
        }
    }
    while (!fin_jeu);

    afficher_fin_partie(&plateau, joueurs, nb_joueurs);

    return 0;
}

void effacer_instructions()
{
    gotoligcol(22, 0);
    int i;
    for (i = 0 ; i < 1000; i++)
    {
        printf("   ");
    }
    gotoligcol(22, 0);
}

void afficher_liste_joueurs(t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs, t_plateau *plateau, t_joueur *joueur_courant)
{
    printf("\n");
    int num_joueur;
    for (num_joueur = 0; num_joueur < nb_joueurs; num_joueur++)
    {
        changer_print_couleur(joueurs[num_joueur].couleur_pieces);
        if (peut_jouer_joueur(&joueurs[num_joueur], plateau))
        {
            if (joueur_courant->est_ia)
            {
                printf("L'ordinateur %s est encore dans la partie.\n", joueurs[num_joueur].pseudo);
            }
            else
            {
                printf("Le joueur %s est encore dans la partie.\n", joueurs[num_joueur].pseudo);
            }
        }
        else
        {
            if (joueur_courant->est_ia)
            {
                printf("L'ordinateur %s est elimine.\n", joueurs[num_joueur].pseudo);
            }
            else
            {
                printf("Le joueur %s est elimine.\n", joueurs[num_joueur].pseudo);
            }
        }
    }
    printf("\n");

    changer_print_couleur(joueur_courant->couleur_pieces);
    if (joueur_courant->est_ia)
    {
        printf("L'ordinateur %s est en train de reflechir...\n", joueur_courant->pseudo);
    }
    else
    {
        printf("%s, a vous de jouer !\n", joueur_courant->pseudo);
    }
    reset_print_couleur();
}

void afficher_fin_partie(t_plateau *plateau, t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs)
{
    afficher_plateau(plateau);
    effacer_instructions();
    printf("Fin du jeu !\n\n");

    // Statistiques de la partie
    int num_joueur;
    for (num_joueur = 0; num_joueur < nb_joueurs; num_joueur++)
    {
        changer_print_couleur(joueurs[num_joueur].couleur_pieces);
        if (joueurs[num_joueur].est_ia)
        {
            printf("Il restait %d piece(s) a poser pour l'ordinateur %s.\n", nb_pieces_restantes_joueur(&joueurs[num_joueur]), joueurs[num_joueur].pseudo);
        }
        else
        {
            printf("Il restait %d piece(s) a poser pour le joueur %s.\n", nb_pieces_restantes_joueur(&joueurs[num_joueur]), joueurs[num_joueur].pseudo);
        }
    }
    reset_print_couleur();

    // On détermine le gagnant
    t_joueur *joueur_gagant = &joueurs[0];
    for (num_joueur = 0; num_joueur < nb_joueurs; num_joueur++)
    {
        int nb_pieces_restantes_joueur_courant = nb_pieces_restantes_joueur(&joueurs[num_joueur]);
        int nb_pieces_restantes_joueur_gagnant = nb_pieces_restantes_joueur(joueur_gagant);
        if (nb_pieces_restantes_joueur_courant < nb_pieces_restantes_joueur_gagnant)
        {
            joueur_gagant = &joueurs[num_joueur];
        }
    }

    t_joueur *joueurs_ex_aequo[NB_JOUEURS_MAX];
    joueurs_ex_aequo[0] = joueur_gagant;
    int nb_joueurs_ex_aequo = 1;
    for (num_joueur = 0; num_joueur < nb_joueurs; num_joueur++)
    {
        int nb_pieces_restantes_joueur_courant = nb_pieces_restantes_joueur(&joueurs[num_joueur]);
        int nb_pieces_restantes_joueur_gagnant = nb_pieces_restantes_joueur(joueur_gagant);
        if (joueur_gagant != &joueurs[num_joueur] &&
            nb_pieces_restantes_joueur_courant == nb_pieces_restantes_joueur_gagnant)
        {
            joueurs_ex_aequo[nb_joueurs_ex_aequo] = &joueurs[num_joueur];
            nb_joueurs_ex_aequo++;
        }
    }

    // Gagnant
    if (nb_joueurs_ex_aequo == 1)
    {
        changer_print_couleur(joueur_gagant->couleur_pieces);
        printf("\nLe gagnant est %s !\n", joueur_gagant->pseudo);
    }
    // Ex-aequo
    else
    {
        printf("\nLes gagnants ex-aequo sont :\n");
        for (num_joueur = 0; num_joueur < nb_joueurs_ex_aequo; num_joueur++)
        {
            changer_print_couleur(joueurs_ex_aequo[num_joueur]->couleur_pieces);
            printf("- %s\n", joueurs_ex_aequo[num_joueur]->pseudo);
        }
    }
    reset_print_couleur();
}

t_joueur *selectionner_joueur_suivant(t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs, t_joueur *joueur_courant, t_plateau *plateau, int *num_joueur)
{
    t_joueur *joueur_suivant;
    do
    {
        (*num_joueur)++;
        joueur_suivant = &joueurs[*num_joueur % nb_joueurs];

        // Aucun joueur ne peut plus jouer
        if (joueur_suivant == joueur_courant &&
            !peut_jouer_joueur(joueur_suivant, plateau))
        {
            return NULL;
        }
    }
    while (!peut_jouer_joueur(joueur_suivant, plateau));

    return joueur_suivant;
}
