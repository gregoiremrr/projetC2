#include <stdio.h>
#include <stdlib.h>

#include "monde.h"
#include "creerPerso.h"

int* caseLibre(Monde* monde, Personnage* chateau, nomPerso typeProd){
    int k = 1;
    int i = chateau->x, j = chateau->y;
    int* tab = malloc(2*sizeof(int));
    while(k!=8){
        printf("%d\n", k);
        for(int n = -k; n<=k; n++){
            if((i-k >= 0 && i-k <= 7 && j+n >= 0 && j+n <= 7) && monde->plateau[i-k][j+n]->perso == NULL){
                tab[0] = i-k;
                tab[1] = j+n;
                return tab;
            }
        }
        for(int n = -k; n<=k; n++){
            if ((i+k >= 0 && i+k <= 7 && j+n >= 0 && j+n <= 7) && monde->plateau[i+k][j+n]->perso == NULL){
                tab[0] = i+k;
                tab[1] = j+n;
                return tab;
            }
        }
        for(int n = -k+1; n<=k-1; n++){
            if ((i+n >= 0 && i+n <= 7 && j-k >= 0 && j-k <= 7) && monde->plateau[i+n][j-k]->perso == NULL){
                tab[0] = i+n;
                tab[1] = j-k;
                return tab;
            }
        }
        for(int n = -k+1; n<=k-1; n++){
            if ((i+n >= 0 && i+n <= 7 && j+k >= 0 && j+k <= 7) && monde->plateau[i+n][j+k]->perso == NULL){
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
    Personnage* prev = chateau;
    while (prev->next){
        prev = prev->next;
    }
    nvPerso->previous = prev;
    nvPerso->next = NULL;
    nvPerso->previous->next = nvPerso;
    monde->plateau[cLibre[0]][cLibre[1]]->perso = nvPerso;
}