#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pieces_loader.h"

/*
t_piece* charger_pieces(char const * const chemin_dossier_pieces)
{
    int const NB_PIECES_MAX = 21;
    t_piece *pieces = malloc(NB_PIECES_MAX * sizeof(t_piece));
    DIR *dossierPieces = opendir(chemin_dossier_pieces);
    struct dirent *entreeDossierCourant;
    while ((entreeDossierCourant = readdir(dossierPieces)) != NULL)
    {
        char const * const NOM_ENTREE_DOSSIER_COURANT = entreeDossierCourant->d_name;
        int const EST_DOSSIER_COURANT_OU_PARENT = strcmp(NOM_ENTREE_DOSSIER_COURANT, ".") == 0 || strcmp(NOM_ENTREE_DOSSIER_COURANT, "..") == 0;
        if (!EST_DOSSIER_COURANT_OU_PARENT)
        {
            char cheminFichierPiece[64] = "";
            strcpy(cheminFichierPiece, chemin_dossier_pieces);
            strcat(cheminFichierPiece, NOM_ENTREE_DOSSIER_COURANT);
            FILE *fichierPiece = fopen(cheminFichierPiece, "r");
            fclose(fichierPiece);
            printf("%s\n", NOM_ENTREE_DOSSIER_COURANT);
        }
    }
    closedir(dossierPieces);

    return pieces;
}

vpod charger_pieces2(char const * const chemin_dossier_pieces)
{
    int const NB_PIECES_MAX = 21;
    t_piece piece;

    return piece;
}
*/
