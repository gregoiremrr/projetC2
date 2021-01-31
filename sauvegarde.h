#ifndef SAVE
#define SAVE

#include <stdio.h>
#include <stdlib.h>

#include "monde.h"

void save(FILE* fichier, Monde* monde, Couleur couleur, int tresorRouge, int tresorBleu);

int lenFichier(FILE* fichier);

Monde* chargeFile(FILE* fichier, int* debut, int *tresorBleu, int *tresorRouge);

int charEstDans(char c, char* str);

#endif