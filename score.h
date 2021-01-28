#ifndef SCORE
#define SCORE

#include <stdio.h>
#include <stdlib.h>

#include "monde.h"

typedef struct score {
	int valeur;
	char nom[256];
} Score;

int score(Monde* monde, int tresorBleu, int tresorRouge, int tourNum);

void ajouteScore(int newScore);

#endif