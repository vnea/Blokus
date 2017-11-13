#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#define MAX_JOUEURS 4

#include "joueur.h"

typedef struct jeu
{
    t_joueur *joueurs[MAX_JOUEURS];
    int nb_joueurs;

} t_jeu;

void initialiser_jeu(t_jeu *jeu, t_joueur joueurs[MAX_JOUEURS], int nb_joueurs);
int fin_du_jeu(t_jeu *jeu);

#endif // JEU_H_INCLUDED
