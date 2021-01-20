#include <stdio.h>
#include <stdlib.h>

#include "Tour.h"
#include "monde.h"

void ifVoisin(Monde* monde, Personnage *persoV){
    if (monde->plateau[persoV->x][persoV->y] != NULL &&
     monde->plateau[persoV->x][persoV->y]->perso->couleur == persoV->couleur){
         persoV->vNext = monde->plateau[persoV->x][persoV->y]->perso;
         monde->plateau[persoV->x][persoV->y]->perso->vPrevious = persoV;
    }
    /*else if (monde->plateau[perso->x][perso->y] != NULL &&
     monde->plateau[perso->x][perso->y]->perso->couleur != persoV->couleur)
        combat(monde, persoV);
    }*/
}