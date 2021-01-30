#include <stdio.h>
#include <stdlib.h>

#include "creerPerso.h"
#include "monde.h"

//La fonction permet trouver la case libre la plus proche du chateau
int* caseLibre(Monde* monde, Personnage* chateau, nomPerso typeProd){
    int k = 1;
    int i = chateau->x, j = chateau->y;
    int* tab = malloc(2*sizeof(int));
    while(k!=8){
        for(int n = -k; n<=k; n++){
            if((i-k >= 0 && i-k <= 7 && j+n >= 0 && j+n <= 7) && monde->plateau[i-k][j+n]->perso == NULL && monde->plateau[i-k][j+n]->chateau == NULL){
                tab[0] = i-k;
                tab[1] = j+n;
                return tab;
            }
        }
        for(int n = -k; n<=k; n++){
            if ((i+k >= 0 && i+k <= 7 && j+n >= 0 && j+n <= 7) && monde->plateau[i+k][j+n]->perso == NULL && monde->plateau[i+k][j+n]->chateau == NULL){
                tab[0] = i+k;
                tab[1] = j+n;
                return tab;
            }
        }
        for(int n = -k+1; n<=k-1; n++){
            if ((i+n >= 0 && i+n <= 7 && j-k >= 0 && j-k <= 7) && monde->plateau[i+n][j-k]->perso == NULL && monde->plateau[i+n][j-k]->chateau == NULL){
                tab[0] = i+n;
                tab[1] = j-k;
                return tab;
            }
        }
        for(int n = -k+1; n<=k-1; n++){
            if ((i+n >= 0 && i+n <= 7 && j+k >= 0 && j+k <= 7) && monde->plateau[i+n][j+k]->perso == NULL && monde->plateau[i+n][j+k]->chateau == NULL){
                tab[0] = i+n;
                tab[1] = j+k;
                return tab;
            }
        }
        k++;
        if (k==8){
            tab[0] = 0;
            tab[1] = 0;
            return tab;
        }
    }
    printf("Le plateau est rempli... Le personnage ne peut pas etre place !");
    return NULL;
}

void creerPersonnage(Monde* monde, Personnage* chateau, nomPerso typeProd){
    Personnage* nvPerso = malloc(sizeof(Personnage));
    nvPerso->nom = typeProd;
    nvPerso->couleur = chateau->couleur;
    int* cLibre = caseLibre(monde, chateau, chateau->typeProd);
    nvPerso->x = cLibre[0];
    nvPerso->y = cLibre[1];
    nvPerso->xDest = nvPerso->x;
    nvPerso->yDest = nvPerso->y;
    nvPerso->vNext = NULL;
    nvPerso->vPrevious = NULL;
    nvPerso->num = incrementAndGet(nvPerso);
    if (typeProd == Seigneur) {
        nvPerso->coupDeProd = 20;
    } else if (typeProd == Guerrier) {
        nvPerso->coupDeProd = 5;
    } else {
        nvPerso->coupDeProd = 1;
    }
    Personnage* prev = chateau;
    while (prev->next){
        prev = prev->next;
    }
    nvPerso->previous = prev;
    nvPerso->next = NULL;
    nvPerso->previous->next = nvPerso;
    monde->plateau[cLibre[0]][cLibre[1]]->perso = nvPerso;
}

void deletePerso(Monde* monde, Personnage* perso){printf("voila1\n");
    if (perso->nom == Chateau) {printf("voila2\n");
        monde->plateau[perso->x][perso->y]->chateau = NULL;
        Personnage* persoInter = perso;
        if (perso->couleur == Bleu) {printf("voila3\n");
            if (perso == monde->chateauBleu) {printf("voila4\n");
                if (perso->vNext != NULL) {
                    monde->chateauBleu = perso->vNext;
                } else {printf("voila5\n");
                    printf("L'equipe rouge a gagne !\n");
                    partie = 0;
                }
            }
        } else {printf("voila6\n");
            if (perso == monde->chateauRouge) {printf("voila7\n");
                if (perso->vNext != NULL) {
                    monde->chateauRouge = perso->vNext;
                } else {printf("voila8\n");
                    printf("L'equipe bleue a gagne !\n");
                    partie = 0;
                }
            }
        }
        while (persoInter->next != NULL) {printf("voila9\n");
            persoInter = persoInter->next;
            if (persoInter->previous->vPrevious == NULL) {printf("voila10\n");
                monde->plateau[persoInter->previous->x][persoInter->previous->y]->perso = persoInter->previous->vNext;
            } else {printf("voila\n");
                persoInter->previous->vPrevious->vNext = persoInter->previous->vNext;
            }
            if (persoInter->previous->vNext != NULL) {printf("voila11\n");
                persoInter->previous->vNext->vPrevious = persoInter->previous->vPrevious;printf("voila11a\n");
            }printf("voila11b\n");
            if (persoInter->previous->previous != NULL) {
                persoInter->previous->previous->next = persoInter->previous->next;printf("voila11c\n");
            }printf("voila12\n");
            if (persoInter->previous->nom == Manant) {printf("oke1");
                int x = persoInter->previous->x, y = persoInter->previous->y;
                free(persoInter->previous);
                if (persoInter->previous->couleur == Bleu) {printf("oke2");
                    initPerso(monde, Manant, x, y, Rouge, monde->chateauRouge);
                } else {printf("oke3");
                    initPerso(monde, Manant, x, y, Bleu, monde->chateauBleu);
                }
            } else {printf("oke4");
                free(persoInter->previous);
            }printf("oke5");
            persoInter->previous = NULL;printf("oke6");
        }printf("hehe1\n");
        if (persoInter->vPrevious == NULL) {printf("hehe2\n");
            monde->plateau[persoInter->x][persoInter->y]->perso = persoInter->vNext;
        } else {printf("hehe3\n");
            persoInter->vPrevious->vNext = persoInter->vNext;
        }printf("hehe4\n");
        if (persoInter->vNext != NULL) {printf("hehe5\n");
            persoInter->vNext->vPrevious = persoInter->vPrevious;
        }printf("hehe6\n");
        if (persoInter->next != NULL) {printf("hehe7\n");
            persoInter->next->previous = persoInter->previous;
        }printf("hehe8\n");
        if (persoInter->nom == Manant) {
            int x = persoInter->x, y = persoInter->y;printf("ok1");
            free(persoInter);printf("ok2");
            if (persoInter->couleur == Bleu) {
                initPerso(monde, Manant, x, y, Rouge, monde->chateauRouge);
            } else {printf("ok3");
                initPerso(monde, Manant, x, y, Bleu, monde->chateauBleu);
            }
        } else {printf("ok4");
            free(persoInter);
        }
    } else {
        if (perso->vPrevious == NULL) {
            monde->plateau[perso->x][perso->y]->perso = perso->vNext;
        } else {
            perso->vPrevious->vNext = perso->vNext;
        }
        if (perso->vNext != NULL) {
            perso->vNext->vPrevious = perso->vPrevious;
        }
        perso->previous->next = perso->next;
        if (perso->next != NULL) {
            perso->next->previous = perso->previous;
        }
        free(perso);
    }
}

void creerChateau(Monde* monde, Personnage* perso){
    int x = perso->x;
    int y = perso->y;
    Personnage* chateau = perso;
    while(chateau->previous != NULL){
        chateau = chateau->previous;
    }
    Couleur couleur = perso->couleur;
    deletePerso(monde, perso);
    Personnage* nvChateau = malloc(sizeof(Personnage));
    nvChateau->nom = Chateau;
    nvChateau->couleur = couleur;
    nvChateau->x = x;
    nvChateau->y = y;
    nvChateau->xDest = nvChateau->x;
    nvChateau->yDest = nvChateau->y;
    nvChateau->coupDeProd = 30;
    nvChateau->vNext = NULL;
    nvChateau->vPrevious = chateau;
    chateau->vNext = nvChateau;
    nvChateau->tpsProd = 0;
    nvChateau->typeProd = nul;
    nvChateau->next = NULL;
    nvChateau->previous = NULL;
    nvChateau->num = incrementAndGet(nvChateau);
    monde->plateau[x][y]->chateau = nvChateau;
}