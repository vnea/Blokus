#include <stdio.h>

#include <stdlib.h>

#include "../include/console.h"
#include "../include/plateau.h"
#include "../include/piece.h"
#include "../include/bloc.h"
#include "../include/affichage.h"

int main()
{
    t_piece pieces[NB_PIECES_MAX];
    charger_pieces(pieces);


    t_plateau plateau;
    initialiser_plateau(&plateau);
    afficher_plateau(&plateau);

    if (peut_poser_piece_dans_plateau(&plateau, &pieces[0], 0, 0))
    {
        poser_piece(&plateau, &pieces[0], 0, 0);
    }


    printf("\n");
    afficher_plateau(&plateau);
/*

    if (peut_poser_piece_dans_plateau(&plateau, &pieces[1], 0, 0))
    {
        poser_piece(&plateau, &pieces[1], 0, 0);
    }

    printf("\n");
    afficher_plateau(&plateau);

    if (peut_poser_piece_dans_plateau(&plateau, &pieces[1], 0, 1))
    {
        poser_piece(&plateau, &pieces[1], 0, 1);
    }
    printf("\n");
    afficher_plateau(&plateau);
*/
    return 0;
}
