#ifndef DEPLACEMENT
#define DEPLACEMENT

#include "monde.h"

void gereDeplacement(Monde* monde, Personnage* perso);

int engageCombatPerso(Monde* monde, Personnage* persoAttaque, Personnage* persoDefend);

void verifCombat(Monde* monde, Personnage* manant);

#endif