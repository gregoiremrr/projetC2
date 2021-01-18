#include <stdio.h>

#include "monde.h"

int main() {
    Monde* monde = initMonde();
    int tresorRouge = 50, tresorBleu = 50;
    afficheMonde(monde);

    return 0;
}