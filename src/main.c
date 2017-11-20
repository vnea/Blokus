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

#define NB_JOUEURS_MAX 4
#define BUFFER 64

void effacer_instructions();
void afficher_liste_joueurs(t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs, t_plateau *plateau, t_joueur *joueur_courant);
t_joueur *selectionner_joueur_suivant(t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs, t_joueur *joueur_courant, t_plateau *plateau, int *num_joueur);

int main()
{
    // Creation pieces
    t_piece pieces[NB_PIECES_MAX];
    charger_pieces(pieces);

    // Creation des joueurs
    int nb_joueurs;
    do
    {
        printf("Nombre de joueurs (entre 2 et %d joueurs) : ", NB_JOUEURS_MAX);
        scanf(" %d", &nb_joueurs);
    } while (nb_joueurs < 2 || nb_joueurs > NB_JOUEURS_MAX);

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
        char pseudo[BUFFER];
        do {
            printf("Pseudo du joueur %d : ", num_joueur + 1);
            fflush(stdin);
            fgets(pseudo, BUFFER, stdin);
        } while (strlen(pseudo) == 1);

        pseudo[strlen(pseudo) - 1] = '\0';
        initialiser_joueur(&joueurs[num_joueur], pseudo, pieces, couleurs_joueurs[num_joueur], 0);
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

        // Selectionner piece
        int indice_piece;
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
        } while (piece < 'A' || piece > 'U' || joueur_courant->piece_deja_posee[indice_piece]);
        joueur_courant->piece_selectionnee = &joueur_courant->pieces[indice_piece];
        afficher_piece_selectionnee_joueur(joueur_courant);

        // Selectionner les rotations/inversions
        SELECTION_ROTATION_INVERSION:
        effacer_instructions();
        afficher_liste_joueurs(joueurs, nb_joueurs, &plateau, joueur_courant);
        printf("Rotation / Inversion (touches G-D-I, Entree pour ne rien faire ou * pour retour) : ");

        char mouvement[BUFFER];
        fflush(stdin);
        fgets(mouvement, BUFFER, stdin);
        int i;
        for (i = 0; i < strlen(mouvement); i++)
        {
            if (mouvement[i] == 'G')
            {
                rotation_gauche_piece(joueur_courant->piece_selectionnee);
            }
            else if (mouvement[i] == 'D')
            {
                rotation_droite_piece(joueur_courant->piece_selectionnee);
            }
            else if (mouvement[i] == 'I')
            {
                inverser_piece(joueur_courant->piece_selectionnee);
            }
            else if (mouvement[i] == '*')
            {
                goto SELECTION_PIECE;
            }
        }
        afficher_piece_selectionnee_joueur(joueur_courant);

        // Selectionner position de la piece
        t_coord pos_piece_dans_plateau;
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
        } while (!peut_poser_piece_dans_plateau(&plateau, joueur_courant->piece_selectionnee, &pos_piece_dans_plateau, joueur_courant->premier_coup));

        poser_piece_dans_plateau(&plateau, joueur_courant->piece_selectionnee, &pos_piece_dans_plateau);
        joueur_courant->premier_coup = 0;
        joueur_courant->piece_deja_posee[indice_piece] = 1;

        fin_jeu = nb_pieces_restantes_joueur(joueur_courant) == 0;
        if (!fin_jeu)
        {
            joueur_courant = selectionner_joueur_suivant(joueurs, nb_joueurs, joueur_courant, &plateau, &num_joueur);
            fin_jeu = joueur_courant == NULL;
        }
    } while (!fin_jeu);

    afficher_plateau(&plateau);
    effacer_instructions();
    printf("Fin du jeu !\n\n");

    // Statistiques de la partie
    for (num_joueur = 0; num_joueur < nb_joueurs; num_joueur++)
    {
        changer_print_couleur(joueurs[num_joueur].couleur_pieces);
        printf("Il restait %d piece(s) a poser pour le joueur %s.\n", nb_pieces_restantes_joueur(&joueurs[num_joueur]), joueurs[num_joueur].pseudo);
        reset_print_couleur();
    }

    // On détermine le gagnant ou les ex-aequo
    /*t_joueur *joueur_gagant = &joueurs[0];
    t_joueur *joueurs_ex_aequo[NB_MAX_JOUEURS];
    joueurs_ex_aequo[0] = joueur_gagant;
    int nb_joueurs_ex_aequo = 1;
    for (num_joueur = 1; num_joueur < nb_joueurs; num_joueur++)
    {
        int nb_pieces_restantes_joueur_courant = nb_pieces_restantes_joueur(&joueurs[num_joueur]);
        int nb_pieces_restantes_joueur_gagnant = nb_pieces_restantes_joueur(joueur_gagant);
        if (nb_pieces_restantes_joueur_courant < nb_pieces_restantes_joueur_gagnant)
        {
            joueur_gagant = &joueurs[num_joueur];
        }
        if (nb_pieces_restantes_joueur_courant == nb_pieces_restantes_joueur_gagnant)
        {
            joueurs_ex_aequo[nb_joueurs_ex_aequo] = &joueurs[num_joueur];
            nb_joueurs_ex_aequo++;
        }
    }

    // Gagnant
    if (nb_joueurs_ex_aequo == 2)
    {

    }
    // Ex-aequo
    else
    {

    }
    */
    return 0;
}

void effacer_instructions()
{
    gotoligcol(0, 28);
    int i;
    for (i = 0 ; i < 1000; i++)
    {
        printf("   ");
    }
    gotoligcol(0, 28);
}

t_joueur *selectionner_joueur_suivant(t_joueur joueurs[NB_JOUEURS_MAX], int nb_joueurs, t_joueur *joueur_courant, t_plateau *plateau, int *num_joueur)
{
    t_joueur *joueur_suivant;
    do
    {
        (*num_joueur)++;
        joueur_suivant = &joueurs[*num_joueur % nb_joueurs];
        if (joueur_suivant == joueur_courant)
        {
            return NULL;
        }
    } while (!peut_jouer_joueur(joueur_suivant, plateau));

    return joueur_suivant;
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
            printf("Le joueur %s est encore dans la partie.\n", joueurs[num_joueur].pseudo);
        }
        else
        {
            printf("Le joueur %s est elimine.\n", joueurs[num_joueur].pseudo);
        }
    }
    printf("\n");

    changer_print_couleur(joueur_courant->couleur_pieces);
    printf("%s, a vous de jouer !\n", joueur_courant->pseudo);
    reset_print_couleur();
}
