#include <stdio.h>
#include <stdlib.h>

#include "Tour.h"
#include "monde.h"


void ifVoisins(Monde* monde, Personnage* perso){
    if (monde->plateau[perso->x][perso->y]->perso == NULL){
        monde->plateau[perso->x][perso->y]->perso = perso;
    }
    if(monde->plateau[perso->x][perso->y]->perso != NULL 
        && monde->plateau[perso->x][perso->y]->perso->couleur == perso->couleur){
            perso->vNext = monde->plateau[perso->x][perso->y]->perso;
            monde->plateau[perso->x][perso->y]->perso->vPrevious = perso;

        }
}