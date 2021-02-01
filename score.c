#include <stdio.h>
#include <stdlib.h>

#include "score.h"
#include "monde.h"

//calcul du score selon une formule choisie
int score(Monde* monde) {
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
    scoreF = scoreB - scoreR;
    if (scoreF < 0 ) {
        scoreF = ((-scoreF)*15) + *tresorRouge;
        printf("Les rouges remportent la partie avec pour score : %d\n", scoreF);
    } else if (scoreF > 0) {
        scoreF = (scoreF*15) + *tresorBleu;
        printf("Les bleus remportent la partie avec pour score : %d\n", scoreF);
    } else {
        printf("Il y a égalité... Personne n'a gagné (score nul)");
    }
    return scoreF;
}

//recuperation dans le tableau de maillon des scores
//et noms et reecriture du fichier avec le nouveau score en plus
void ajouteScore(int newScore) {
	FILE* fichierR = fopen("sauvegarde.txt", "r");
    
    if (fichierR != NULL){
        char a, nom[256];
		rewind(fichierR);
		
		Score** maillons = malloc(11*sizeof(Score*));
		for (int i = 0; i<11; i++) {
			maillons[i] = malloc(sizeof(Score));
			maillons[i]->valeur = -1;
			maillons[i]->nom[0] = 'o';
			maillons[i]->nom[1] = '\0';
		}
		int j = 0;
		while (j<10 && a != -1) {
            fscanf(fichierR, "%d %s", &(maillons[j]->valeur), maillons[j]->nom);
			fseek(fichierR, 2, SEEK_CUR);
			a = fgetc(fichierR);
			fseek(fichierR, -3, SEEK_CUR);
			j++;
        }
		fclose(fichierR);

		FILE* fichierW = fopen("sauvegarde.txt", "w+");
		if (fichierW != NULL) {
			j = 0;
			while (maillons[j]->valeur >= newScore && j < 10) {
				fprintf(fichierW, "%d %s\n", maillons[j]->valeur, maillons[j]->nom);
				j++;
			}
			if (j<10) {
				printf("Entrez votre nom :\n");
                scanf("%s", nom);
				fprintf(fichierW, "%d %s\n", newScore, nom);
				while (j<9 && maillons[j]->valeur > 0) {
					fprintf(fichierW, "%d %s\n", maillons[j]->valeur, maillons[j]->nom);
					j++;
				}
			}
			fclose(fichierW);
		} else {
			printf("Erreur lors de l'ouverture du fichier...\n");
		}
        //free des maillons
        for (int i = 0; i < 11; i++) {
            free(maillons[i]);
        }
        free(maillons);
	} else {
		FILE* f = fopen("sauvegarde.txt", "w");
		if (f != NULL) {
			fclose(f);
			ajouteScore(newScore);
		} else {
			printf("Erreur lors de la créaton du fichier de sauvegarde...\n");
		}
    }
}