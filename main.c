#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED '\033[31m'
#define BLUE '\033[34m'

#include "monde.h"
#include "creerPerso.h"
#include "actionEtTour.h"

int partie = 1;

int main() {
    Monde* monde = initMonde();
    int* tresorRouge = malloc(sizeof(int)),* tresorBleu = malloc(sizeof(int));
    *tresorRouge = 50;
    *tresorBleu = 50;
    int tourNum = 0;
    srand(time(NULL));
    int debut = rand()%2;
    afficheMonde(monde, *tresorBleu, *tresorRouge, Bleu, 1);
    printf("\n");
    while(partie == 1){
        if(tourNum%2==debut){
            printf("L'équipe \033[34mbleue\033[37m\033[49m joue !\n\n");
            tour(monde, Bleu, tresorBleu, tresorRouge);
        } else {
            printf("L'équipe \033[31mrouge\033[37m\033[49m joue !\n\n");
            tour(monde, Rouge, tresorRouge, tresorBleu);
        }
        tourNum++;
    }
    return 0;
}