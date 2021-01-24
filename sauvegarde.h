#ifndef SAVE
#define SAVE

#include <stdio.h>
#include <stdlib.h>

#include "monde.h"

void save(FILE* fichier, Monde* monde, Couleur couleur, int tresorRouge, int tresorBleu);

Monde* chargeFile(FILE* fichier, int* debut, int *tresorBleu, int *tresorRouge);
#endif