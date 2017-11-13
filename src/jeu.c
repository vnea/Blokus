#include "../include/jeu.h"

void initialiser_jeu(t_jeu *jeu, t_joueur joueurs[MAX_JOUEURS], int nb_joueurs)
{
    int num_joueur;
    for (num_joueur = 0; num_joueur < nb_joueurs; num_joueur++)
    {
        jeu->joueurs[num_joueur] = &joueurs[num_joueur];
    }
    jeu->nb_joueurs = nb_joueurs;
}

int fin_du_jeu(t_jeu *jeu)
{

    return 1;
}
