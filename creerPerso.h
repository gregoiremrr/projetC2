#ifndef CREERPERSO
#define CREERPERSO

#include <stdio.h>
#include<stdlib.h>

#include "monde.h"
//#include "tour.h"

void creerPersonnage(Monde* monde, Personnage* chateau, nomPerso typeProd);

void creerChateau(Monde* monde, Personnage* perso);

int* caseLibre(Monde* monde, Personnage* chateau, nomPerso typeProd);

void deletePerso(Monde* monde, Personnage* perso);

#endif