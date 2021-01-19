#include <stdio.h>
#include <stdlib.h>

int* caseLibre(Monde* monde, Personnage* chateau, nomPerso typeProd){
    int k = 0; t=0
    int i = chateau->x, j = chateau->y;
    while(1)
        if(i-k >= 0){
            if ( monde->plateau[i][j]->perso == NULL)
                return 
            else if (j-t >= 0){
                if (monde->plateau[i][j-t]->perso == NULL)
                    return 
            }
            else if(j+t < = 7){
                if (monde->plateau[i][j+t]->perso == NULL)
                    return 
            }
            i-=1;
            t++;
            
        }
    }
}

void creerPersonnage(Monde* monde, Personnage* chateau, nomPerso typeProd){
    Personnage* nvPerso = malloc(sizeof(Personnage));
    nvPerso->nom = typeProd;
    nvPerso->couleur = chateau->couleur;
    int* cLibre = caseLibre();
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
    monde->plateau[x][y]->perso = nvPerso;
}
while(monde->plateau[i][j]->perso != NULL){
        if (k%4==0) {
            i-=k;
            j-=k;
        } else if (k%4==1) {

        } else if (k%4==2) {

        }else {

        }
        if(p == chateau->y + t){
            k++;
        }