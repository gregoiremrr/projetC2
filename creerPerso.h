#ifndef CREERPERSO
#define CREERPERSO

#include <stdio.h>
#include<stdlib.h>

#include "monde.h"

int* caseLibre(Monde* monde, Personnage* chateau, nomPerso typeProd);

void creerPersonnage(Monde* monde, Personnage* chateau, nomPerso typeProd);

void deletePerso(Monde* monde, Personnage* perso);

void creerChateau(Monde* monde, Personnage* perso);

#endif