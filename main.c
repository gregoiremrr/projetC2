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
            printf("L'équipe bleue joue\n");
            tour(monde, Bleu, &tresorBleu);
        } else {
            printf("L'équipe rouge joue\n");
            tour(monde, Rouge, &tresorRouge);
        }
        tourNum++;
    }
    return 0;
}