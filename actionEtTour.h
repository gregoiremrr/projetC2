#ifndef ACTION
#define ACTION

#include <stdio.h>
#include<stdlib.h>

#include "monde.h"

void actionChateau(Monde* monde, Personnage* chateau, int* tresor, int* tresor2);

void actionSeigneur(Monde* monde, Personnage* perso, int* tresor);

void actionGuerrier(Monde* monde, Personnage* perso);

void actionManant(Monde* monde, Personnage* perso, int* tresor);

void tour(Monde* monde, Couleur couleur, int* tresor, int* tresor2);

#endif