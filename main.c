#include <stdio.h>

#include "monde.h"
#include "creerPerso.h"

int main() {
    Monde* monde = initMonde();
    int tresorRouge = 50, tresorBleu = 50;
    afficheMonde(monde);
    int* i = caseLibre(monde, monde->chateauRouge, Manant);
    printf("x = %d et y = %d\n", i[0], i[1]);
    return 0;
}