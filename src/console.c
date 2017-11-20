#include <stdio.h>

#include "../include/affichage.h"
#include "../include/console.h"


void afficher_piece(t_piece *piece)
{
    static int y = 0;

    y += 6;

    int i;
    for (i = 0; i < piece->nb_blocs; i++)
    {
        gotoligcol(piece->blocs[i].coord.x + 5, piece->blocs[i].coord.y + y);
        printf("%c", piece->symbole);
    }
}
