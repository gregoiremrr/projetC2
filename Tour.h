#ifndef TOUR
#define TOUR

#include <stdio.h>
#include<stdlib.h>

#include "monde.h"
#include "gererVoisins.h"


void actionChateau(Monde* monde, Personnage* chateau, int* tresor);

void actionSeigneur(Monde* monde, Personnage* perso, int* tresor);

void actionGuerrier(Monde* monde, Personnage* perso, int* tresor);

void actionManant(Monde* monde, Personnage* perso, int* tresor);

int comptePerso(Monde* monde, Couleur couleur);

void tour(Monde* monde, Couleur couleur, int* tresor, int* tresor2);

#endif