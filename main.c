#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monde.h"
#include "creerPerso.h"
#include "Tour.h"

int main() {
    Monde* monde = initMonde();
    int tresorRouge = 50, tresorBleu = 50;
    int tourNum = 0;
    srand(time(NULL));
    int debut = rand()%2;
    while(1){
        if(tourNum%2==debut){
            tour(monde, Bleu, &tresorBleu);
        } else {
            tour(monde, Rouge, &tresorRouge);
        }
        tourNum++;
    }
    return 0;
}