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

void ajouteScore(int newScore) {
    FILE* fichierR = fopen("sauvegarde.txt", "r");
    
    if (fichierR != NULL){
        char a, nom[256], texte[1000];
		int i = 0, j = 0, score, change = 0, compteur = 0;
		rewind(fichierR);
		while (j<10 && change != EOF) {
            change = fscanf(fichierR, "%d %s", &score, nom);
			if (score < newScore) {
				change = 1;
				break;
			}
			j++;
        }
		rewind(fichierR);
		a = fgetc(fichierR);
		do {
			texte[i++] = a;
			a = fgetc(fichierR);
		} while (a != EOF);
		texte[i] = '\0';
		fclose(fichierR);
		
		FILE* fichierW = fopen("sauvegarde.txt", "w+");
        if (fichierW != NULL) {
            i = 0;
            int k = 0;
            do {
                if (compteur == j) {
                    printf("Entrez votre nom :\n");
                    scanf("%s", nom);
                    fprintf(fichierW, "%d %s\n", newScore, nom);
                    compteur++;
                    k = 1;
                } else {
                    fputc(texte[i-k], fichierW);
                    if (texte[i-k] == '\n') {
                        compteur++;
                    }
                }
            } while (texte[++i] != '\0' && compteur < 10);
            
            fclose(fichierW);
        } else {
            printf("Erreur lors de l'ouverture du fichier...\n");
        }
    } else {
        printf("Erreur lors de l'ouverture du fichier...\n");
    }
}