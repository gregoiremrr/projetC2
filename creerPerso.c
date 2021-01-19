#include <stdio.h>
#include <stdlib.h>

Case* caseLibre(){

}

void creerPersonnage(Personnage* chateau, nomPerso typeProd){
    Personnage* nvPerso = malloc(sizeof(Personnage));
    nvPerso->nom = typeProd;
    nvPerso->couleur = chateau->couleur;
    nvPerso->x = //caselibre
    nvPerso->y = //caselibre
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
