#include <stdio.h>
#include <stdlib.h>

#include "monde.h"
#define RED '\033[31m'
#define BLUE '\033[34m'

void initPerso(Monde* monde, nomPerso nom, int x, int y, Couleur couleur, Personnage* chateau){
    Personnage* perso = malloc(sizeof(Personnage));
    perso->nom = nom;
    perso->x = x;
    perso->y = y;
    perso->xDest = x;
    perso->yDest = y;
    perso->couleur = couleur;
    Personnage* prev = chateau;
    while (prev->next){
        prev = prev->next;
    }
    perso->previous = prev;
    perso->next = NULL;
    perso->previous->next = perso;
    if (monde->plateau[x][y]->perso == NULL) {
        monde->plateau[x][y]->perso = perso;
    } else {
        monde->plateau[x][y]->perso->vPrevious = perso;
        perso->vNext = monde->plateau[x][y]->perso;
        perso->vPrevious = NULL;
        monde->plateau[x][y]->perso = perso;
    }
    perso->num = incrementAndGet(perso);
    if (nom == Seigneur) {
        perso->coupDeProd = 20;
    } else if (nom == Guerrier) {
        perso->coupDeProd = 5;
    } else {
        perso->coupDeProd = 1;
    }
    perso->vNext = NULL;
    perso->vPrevious = NULL;
}

Monde* initMonde(void){
    Monde* monde = malloc(sizeof(Monde));
    monde->plateau = malloc(8*sizeof(Case**));
    for(int i = 0; i<8; i++){
        monde->plateau[i] = malloc(8*sizeof(Case*));
        for (int j = 0; j<8; j++){
            monde->plateau[i][j] = malloc(sizeof(Case));
            monde->plateau[i][j]->perso = NULL;
            monde->plateau[i][j]->chateau = NULL;
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
    monde->chateauRouge->coupDeProd = 30;
    monde->chateauRouge->num = incrementAndGet(monde->chateauRouge);
    monde->plateau[7][7]->chateau = monde->chateauRouge;
    monde->plateau[7][7]->perso = NULL;
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
    monde->chateauBleu->coupDeProd = 30;
    monde->chateauBleu->num = incrementAndGet(monde->chateauBleu);
    monde->plateau[0][0]->chateau = monde->chateauBleu;
    monde->plateau[0][0]->perso = NULL;
    initPerso(monde , Seigneur , 0 , 1 , Bleu , monde->chateauBleu);
    initPerso(monde , Manant , 1, 0 , Bleu , monde->chateauBleu);

    return monde;
}
// Initialisation de variables globales qui désignent le nombre de chaque chateau/agent de chaque couleur
int r_chateau = 0, r_guerrier = 0, r_seigneur = 0, r_manant = 0;
int b_chateau = 0, b_guerrier = 0, b_seigneur = 0, b_manant = 0;

int incrementAndGet(Personnage* perso){
    if (perso->couleur == Rouge) {
        switch (perso->nom) {
            case Chateau :
                return ++r_chateau;
            case Guerrier :
                return ++r_guerrier;
            case Seigneur :
                return ++r_seigneur;
            case Manant :
                return ++r_manant;
            default :
                return -1;
        }
    } else {
        switch (perso->nom) {
            case Chateau :
                return ++b_chateau;
            case Guerrier :
                return ++b_guerrier;
            case Seigneur :
                return ++b_seigneur;
            case Manant :
                return ++b_manant;
            default :
                return -1;
        }
    }
}

int nbreMaxPerso(Monde* monde){
    int max = 0, compteur;
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            compteur = 0;
            if (monde->plateau[i][j]->chateau != NULL) {
                compteur++;
            }
            if (monde->plateau[i][j]->perso != NULL) {
                Personnage* persoInter = monde->plateau[i][j]->perso;
                while (persoInter != NULL) {
                    compteur++;
                    persoInter = persoInter->vNext;
                }
            }
            if (compteur > max) {
                max = compteur;
            }
        }
    }
    return max;
}

void afficheMonde(Monde* monde, int tresor, int tresor2, Couleur couleur, int t){
    int max = nbreMaxPerso(monde), nbre;
    if (t==1) {
        if (couleur == Bleu){
            printf("\033[34m Tresor bleu  : %d\n \033[31mTresor rouge : %d\n\033[37m\033[49m", tresor, tresor2);
        } else {
            printf("\033[34m Tresor bleu  : %d\n \033[31mTresor rouge : %d\n\033[37m\033[49m", tresor2, tresor);
        }
    }
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            nbre = 0;
            printf("|");
            if (monde->plateau[i][j]->chateau != NULL) {
                nbre++;
                if (monde->plateau[i][j]->chateau->couleur == Bleu) {
                    printf("\033[34m(Cb%d)\033[37m\033[49m", monde->plateau[i][j]->chateau->num);
                } else {
                    printf("\033[31m(Cr%d)\033[37m\033[49m", monde->plateau[i][j]->chateau->num);
                }
            }
            if (monde->plateau[i][j]->perso != NULL) {
                Personnage* persoInter = monde->plateau[i][j]->perso;
                while (nbre != max) {
                    if (persoInter != NULL) {
                        if (persoInter->nom == Seigneur) {
                            if (persoInter->couleur == Bleu) {
                                printf("\033[34m(Sb%d)\033[37m\033[49m", persoInter->num);
                            } else {
                                printf("\033[31m(Sr%d)\033[37m\033[49m", persoInter->num);
                            }
                        } else if (persoInter->nom == Guerrier) {
                            if (persoInter->couleur == Bleu) {
                                printf("\033[34m(Gb%d)\033[37m\033[49m", persoInter->num);
                            } else {
                                printf("\033[31m(Gr%d)\033[37m\033[49m", persoInter->num);
                            }
                        } else {
                            if (persoInter->couleur == Bleu) {
                                printf("\033[34m(Mb%d)\033[37m\033[49m", persoInter->num);
                            } else {
                                printf("\033[31m(Mr%d)\033[37m\033[49m", persoInter->num);
                            }
                        }
                        persoInter = persoInter->vNext;
                    } else {
                        printf("-----");
                    }
                    nbre++;
                }
            } else {
                while (nbre != max) {
                    printf("-----");
                    nbre++;
                }
            }
        }
        printf("|\n");
    }
}