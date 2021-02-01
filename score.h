#ifndef SCORE
#define SCORE

#include <stdio.h>
#include <stdlib.h>

#include "monde.h"

extern int* tresorBleu;
extern int* tresorRouge;

typedef struct score {
	int valeur;
	char nom[256];
} Score;

int score(Monde* monde, int c);

void ajouteScore(int newScore);

#endif