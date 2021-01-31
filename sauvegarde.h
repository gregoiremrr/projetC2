#ifndef SAVE
#define SAVE

#include <stdio.h>
#include <stdlib.h>

#include "monde.h"

void sauv(FILE* fichier, Monde* monde, Couleur couleur, int tresorRouge, int tresorBleu);

int longueurFichier(FILE* fichier);

Monde* chargeFichier(FILE* fichier, int* debut, int *tresorBleu, int *tresorRouge);

int charEstDans(char c, char* str);

#endif