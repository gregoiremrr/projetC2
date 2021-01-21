#include <stdio.h>
#include <stdlib.h>

#include "Tour.h"
#include "monde.h"
#include "gererVoisins.h"

void gererDep(Monde* monde, Personnage *perso){
    if (perso->vNext != NULL ){
        monde->plateau[perso->x][perso->y]->perso = perso->vNext;
        perso->vNext = NULL;
        if (perso->x > perso->xDest)
            perso->x -= 1;
        else if (perso->x < perso->xDest)
            perso->x += 1;
        if (perso->y > perso->yDest)
            perso->y -= 1;
        else if (perso->y < perso->yDest)
            perso->y += 1;
        ifVoisins(monde, perso);
        }
    else if(perso->vPrevious != NULL){
        monde->plateau[perso->x][perso->y]->perso = perso->vPrevious;
        perso->vPrevious = NULL;
        if (perso->x > perso->xDest)
            perso->x -= 1;
        else if (perso->x < perso->xDest)
            perso->x += 1;
        if (perso->y > perso->yDest)
            perso->y -= 1;
        else if (perso->y < perso->yDest)
            perso->y += 1;
        ifVoisins(monde,perso);
    }
    else if (perso->vPrevious == NULL && perso->vNext == NULL){
        monde->plateau[perso->x][perso->y]->perso = NULL;
        if (perso->x > perso->xDest)
            perso->x -= 1;
        else if (perso->x < perso->xDest)
            perso->x += 1;
        if (perso->y > perso->yDest)
            perso->y -= 1;
        else if (perso->y < perso->yDest)
            perso->y += 1;
        ifVoisins(monde,perso);
        
    }


    

    
}