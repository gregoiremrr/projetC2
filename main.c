#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "string.h"

#define RED '\033[31m'
#define BLUE '\033[34m'

#include "monde.h"
#include "creerPerso.h"
#include "actionEtTour.h"
#include "sauvegarde.h"
#include "score.h"

//variables globales
int partie = 1;
int* tresorBleu,* tresorRouge;

int main() {
    srand(time(NULL));
    int s;
    char sauvegarde;
    char fin;
    char nomFichier[256];
    char charg;
    char nomPartie[256];
    int debut;
    do {
        printf("Voulez-vous charger une partie? (O/N)\n");
        scanf(" %c", &charg);
    } while (charg != 'O' && charg != 'N');
    Monde* monde;
    int tourNum = 0;
    tresorRouge = malloc(sizeof(int));
    tresorBleu = malloc(sizeof(int));
    if (charg == 'N') {
        monde = initMonde();
        *tresorRouge = 50;
        *tresorBleu = 50;
        debut = rand()%2;
    } else {
        FILE* fichier;
        do {
            printf("Rentrez le nom de la partie a charger :(Sans l'extension.got)\n");
            scanf("%s", nomPartie);
            int strLEN = strlen(nomPartie);
            nomPartie[strLEN] = '.';
            nomPartie[strLEN+1] = 'g';
            nomPartie[strLEN+2] = 'o';
            nomPartie[strLEN+3] = 't';
            nomPartie[strLEN+4] = '\0';
            fichier = fopen(nomPartie, "r");
            if (fichier == NULL) {
                printf("Aucune partie de ce nom trouvee...\n");
            }
        } while (fichier == NULL);
        monde = chargeFichier(fichier, tresorBleu, tresorRouge, &debut);
    }
    afficheMonde(monde, *tresorBleu, *tresorRouge, Bleu, 1);
    printf("\n");
    while(partie == 1){
        sauvegarde = 'a';
        if (tourNum > 0) {
            do {
                printf("Voulez-vous sauvegarder ? (O/N)\n");
                scanf(" %c", &sauvegarde);
            } while (sauvegarde != 'O' && sauvegarde != 'N');
        }
        if (sauvegarde == 'O') {
            printf("Entrez le nom du fichier de sauvegarde :(Sans l'extension.got)\n");
            scanf("%s", nomFichier);
            int strLen = strlen(nomFichier);
            nomFichier[strLen] = '.';
            nomFichier[strLen+1] = 'g';
            nomFichier[strLen+2] = 'o';
            nomFichier[strLen+3] = 't';
            nomFichier[strLen+4] = '\0';
            if (tourNum % 2 == debut) {
                sauv(fopen(nomFichier, "w+"), monde, Bleu, *tresorRouge, *tresorBleu);
            } else {
                sauv(fopen(nomFichier, "w+"), monde, Rouge, *tresorRouge, *tresorBleu);
            }
        }
        fin = 'a';
        if (tourNum > 0) {
            do{
                printf("Voulez vous quitter la partie? (O/N)\n");
                scanf(" %c", &fin);
            } while (fin != 'O' && fin !='N');
            if (fin == 'O') {
                printf("Fin de la partie.\n");
                partie = 0;
                s = score(monde, 0);
                ajouteScore(s);
                continue;
            }
        }
        //debut de la partie
        //'debut' s'incremente et la couleur qui joue change donc a chaque tour
        if(tourNum % 2 == debut){
            printf("L'equipe \033[34mbleue\033[37m\033[49m joue !\n\n");
            tour(monde, Bleu, tresorBleu, tresorRouge);
        } else {
            printf("L'equipe \033[31mrouge\033[37m\033[49m joue !\n\n");
            tour(monde, Rouge, tresorRouge, tresorBleu);
        }
        tourNum++;
    }

    //debut des free
    free(tresorBleu);
    free(tresorRouge);
    Personnage* chateauInter = monde->chateauBleu;
    if (chateauInter != NULL) {
        Personnage* persoInter = chateauInter->next;
        while (chateauInter->vNext != NULL) {
            while (persoInter->next != NULL) {
                persoInter = persoInter->next;
                free(persoInter->previous);
            }
            free(persoInter);
            chateauInter = chateauInter->vNext;
            free(chateauInter->vPrevious);
        }
        free(chateauInter);
    }

    chateauInter = monde->chateauRouge;
    if (chateauInter != NULL) {
        Personnage* persoInter = chateauInter->next;
        while (chateauInter->vNext != NULL) {
            while (persoInter->next != NULL) {
                persoInter = persoInter->next;
                free(persoInter->previous);
            }
            free(persoInter);
            chateauInter = chateauInter->vNext;
            free(chateauInter->vPrevious);
        }
        free(chateauInter);
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            free(monde->plateau[i][j]);
        }
    }

    free(monde);
    
    //fin des free
    return 0;
}