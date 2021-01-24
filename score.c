#include <stdio.h>
#include <stdlib.h>

#include "monde.h"

int score(Monde* monde, int tresorBleu, int tresorRouge, int tourNum) {
    Personnage* chateau = monde->chateauBleu;
    Personnage* perso = chateau->next;
    int scoreB = 0;
    int scoreR = 0;
    int scoreF;
    while(chateau != NULL){
        scoreB += 30;
        while(perso) {
            if (perso->nom == Seigneur) {
                scoreB += 20;
            }else if (perso->nom == Guerrier){
                scoreB += 5;
            }else{
                scoreB += 1;
            }
            perso = perso->next;
        }
        chateau = chateau->vNext;
    }
    scoreB += tresorBleu;
    chateau = monde->chateauRouge;
    perso = chateau->next;
    while(chateau != NULL){
        scoreR += 30;
        while(perso) {
            if (perso->nom == Seigneur) {
                scoreR += 20;
            }else if (perso->nom == Guerrier){
                scoreR += 5;
            }else{
                scoreR += 1;
            }
            perso = perso->next;
        }
        chateau = chateau->vNext;
    }
    scoreR += tresorRouge;
    scoreF = scoreB - scoreR;
    if (scoreF < 0 ) {
        scoreF = ((-scoreF)*20)/tourNum;
        printf("Les rouges remportent la partie avec pour score : %d\n", scoreF);
    } else if (scoreF > 0) {
        scoreF = (scoreF*20)/tourNum;
        printf("Les bleus remportent la partie avec pour score : %d\n", scoreF);
    } else {
        printf("Il y a égalité... Personne n'a gagné (score nul)");
    }
    return scoreF;
}

/*void ajouteScore(int score) {

}*/