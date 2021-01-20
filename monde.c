#include <stdio.h>
#include <stdlib.h>

#include "monde.h"

void initPerso(Monde *monde, nomPerso nom, int x, int y, Couleur couleur, Personnage *chateau)
{
    Personnage *perso = malloc(sizeof(Personnage));
    perso->nom = nom;
    perso->x = x;
    perso->y = y;
    perso->xDest = x;
    perso->yDest = y;
    perso->couleur = couleur;
    Personnage *prev = chateau;
    while (prev->next)
    {
        prev = prev->next;
    }
    perso->previous = prev;
    perso->next = NULL;
    perso->previous->next = perso;
    monde->plateau[x][y]->perso = perso;
}

Monde *initMonde(void)
{
    Monde *monde = malloc(sizeof(Monde));
    monde->plateau = malloc(8 * sizeof(Case **));
    for (int i = 0; i < 8; i++)
    {
        monde->plateau[i] = malloc(8 * sizeof(Case *));
        for (int j = 0; j < 8; j++)
        {
            monde->plateau[i][j] = malloc(sizeof(Case));
            monde->plateau[i][j]->perso = NULL;
        }
    }

    monde->chateauRouge = malloc(sizeof(Personnage));
    monde->chateauRouge->nom = Chateau;
    monde->chateauRouge->x = 7;
    monde->chateauRouge->y = 7;
    monde->chateauRouge->xDest = 7;
    monde->chateauRouge->yDest = 7;
    monde->chateauRouge->couleur = Rouge;
    monde->chateauRouge->tpsProd = 0;
    monde->chateauRouge->typeProd = nul;
    monde->chateauRouge->previous = NULL;
    monde->chateauRouge->vNext = NULL;
    monde->chateauRouge->vPrevious = NULL;
    monde->plateau[7][7]->perso = monde->chateauRouge;
    initPerso(monde, Seigneur, 7, 6, Rouge, monde->chateauRouge);
    initPerso(monde, Manant, 6, 7, Rouge, monde->chateauRouge);

    monde->chateauBleu = malloc(sizeof(Personnage));
    monde->chateauBleu->nom = Chateau;
    monde->chateauBleu->x = 0;
    monde->chateauBleu->y = 0;
    monde->chateauBleu->xDest = 0;
    monde->chateauBleu->yDest = 0;
    monde->chateauBleu->couleur = Bleu;
    monde->chateauBleu->tpsProd = 0;
    monde->chateauBleu->typeProd = nul;
    monde->chateauBleu->previous = NULL;
    monde->chateauBleu->vNext = NULL;
    monde->chateauBleu->vPrevious = NULL;
    monde->plateau[0][0]->perso = monde->chateauBleu;
    initPerso(monde, Seigneur, 0, 1, Bleu, monde->chateauBleu);
    initPerso(monde, Manant, 1, 0, Bleu, monde->chateauBleu);

    return monde;
}

// Globales
int r_chateau = 0, r_guerrier = 0, r_seigneur = 0, r_manant = 0;
int b_chateau = 0, b_guerrier = 0, b_seigneur = 0, b_manant = 0;
void afficheMonde(Monde *monde, int tresorBleu, int tresorRouge, Couleur couleur)
{
    if (couleur == Bleu)
    {
        printf("Tresor bleu  : %d\nTresor rouge : %d\n", tresorBleu, tresorRouge);
    }
    else
    {
        printf("Tresor bleu  : %d\nTresor rouge : %d\n", tresorRouge, tresorBleu);
    }

    initCounters();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (monde->plateau[i][j]->perso != NULL)
            {
                if (monde->plateau[i][j]->perso->nom == Chateau)
                {
                    if (monde->plateau[i][j]->perso->couleur == Bleu)
                    {

                        printf("| (Cb%d) ", incrementAndGet(
                                                monde->plateau[i][j]->perso->couleur,
                                                monde->plateau[i][j]->perso->nom));
                    }
                    else
                    {
                        printf("| (Cr%d) ", incrementAndGet(
                                                monde->plateau[i][j]->perso->couleur,
                                                monde->plateau[i][j]->perso->nom));
                    }
                }
                else if (monde->plateau[i][j]->perso->nom == Seigneur)
                {
                    if (monde->plateau[i][j]->perso->couleur == Bleu)
                    {
                        printf("| (Sb%d) ", incrementAndGet(
                                                monde->plateau[i][j]->perso->couleur,
                                                monde->plateau[i][j]->perso->nom));
                    }
                    else
                    {
                        printf("| (Sr%d) ", incrementAndGet(
                                                monde->plateau[i][j]->perso->couleur,
                                                monde->plateau[i][j]->perso->nom));
                    }
                }
                else if (monde->plateau[i][j]->perso->nom == Guerrier)
                {
                    if (monde->plateau[i][j]->perso->couleur == Bleu)
                    {
                        printf("| (Gb%d) ", incrementAndGet(
                                                monde->plateau[i][j]->perso->couleur,
                                                monde->plateau[i][j]->perso->nom));
                    }
                    else
                    {
                        printf("| (Gr%d) ", incrementAndGet(monde->plateau[i][j]->perso->couleur, monde->plateau[i][j]->perso->nom));
                    }
                }
                else if (monde->plateau[i][j]->perso->nom == Manant)
                {
                    if (monde->plateau[i][j]->perso->couleur == Bleu)
                    {
                        printf("| (Mb%d) ", incrementAndGet(
                                                monde->plateau[i][j]->perso->couleur,
                                                monde->plateau[i][j]->perso->nom));
                    }
                    else
                    {
                        printf("| (Mr%d) ", incrementAndGet(
                                                monde->plateau[i][j]->perso->couleur,
                                                monde->plateau[i][j]->perso->nom));
                    }
                }
            }
            else
            {
                printf("| ---- ");
            }
        }
        printf("|\n");
    }
}

void initCounters()
{
    r_chateau = 0;
    r_guerrier = 0;
    r_seigneur = 0;
    r_manant = 0;
    b_chateau = 0;
    b_guerrier = 0;
    b_seigneur = 0;
    b_manant = 0;
}
int incrementAndGet(Couleur color, nomPerso perso)
{
    if (color == Rouge)
    {
        switch (perso)
        {
        case Chateau:
            return ++r_chateau;
        case Guerrier:
            return ++r_guerrier;
        case Seigneur:
            return ++r_seigneur;
        case Manant:
            return ++r_manant;
        default:
            return -1;
        }
    }
    else
    {
        switch (perso)
        {
        case Chateau:
            return ++b_chateau;
        case Guerrier:
            return ++b_guerrier;
        case Seigneur:
            return ++b_seigneur;
        case Manant:
            return ++b_manant;
        default:
            return -1;
        }
    }
}