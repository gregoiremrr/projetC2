#ifndef CREERPERSO
#define CREERPERSO

#include <stdio.h>
#include<stdlib.h>

#include "monde.h"
//#include "tour.h"

void creerPersonnage(Monde* monde, Personnage* chateau, nomPerso typeProd);

int* caseLibre(Monde* monde, Personnage* chateau, nomPerso typeProd);

#endif