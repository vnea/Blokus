#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#define COULEUR_GRIS 8
#define COULEUR_BLEU 11
#define COULEUR_VERT 10
#define COULEUR_ROUGE 12
#define COULEUR_JAUNE 14

void gotoligcol(int lig, int col);
void changer_print_couleur(int couleur);
void reset_print_couleur();
void print_char_couleur(char c, int couleur);

#endif // AFFICHAGE_H_INCLUDED
