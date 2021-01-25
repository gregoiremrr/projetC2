#include <stdio.h>
#include <stdlib.h>

#include "monde.h"
#include "creerPerso.h"

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
    printf("Le plateau est remplis... Le personnage ne peut pas etre place !");
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

void deletePerso(Monde* monde, Personnage* perso){
    if (perso->nom == Chateau) {
        monde->plateau[perso->x][perso->y]->chateau = NULL;
        Personnage* persoInter = perso;
        if (perso->couleur == Bleu) {
            if (perso == monde->chateauBleu) {
                if (perso->vNext != NULL) {
                    monde->chateauBleu = perso->vNext;
                } else {
                    printf("L'equipe rouge a gagne !\n");
                    partie = 0;
                }
            }
        } else {
            if (perso == monde->chateauRouge) {
                if (perso->vNext != NULL) {
                    monde->chateauRouge = perso->vNext;
                } else {
                    printf("L'equipe bleue a gagne !\n");
                    partie = 0;
                }
            }
        }
        while (persoInter->next != NULL) {
            persoInter = persoInter->next;
            if (persoInter->previous->nom == Manant) {
                int x = persoInter->previous->x, y = persoInter->previous->y;
                if (persoInter->previous->couleur == Bleu) {
                    free(persoInter->previous);
                    initPerso(monde, Manant, x, y, Rouge, monde->chateauRouge);
                } else {
                    free(persoInter->previous);
                    initPerso(monde, Manant, x, y, Bleu, monde->chateauBleu);
                }
            } else {
                monde->plateau[persoInter->previous->x][persoInter->previous->y]->perso = NULL;
                free(persoInter->previous);
            }
            persoInter->previous = NULL;
        }
        free(persoInter);
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