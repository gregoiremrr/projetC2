#include <stdio.h>
#include <stdlib.h>

#include "monde.h"

void save(FILE* fichier, Monde* monde, Couleur couleur, int tresorRouge, int tresorBleu){
    fprintf(fichier, "8 8\n");
    if (fichier != NULL){
        if (couleur == Bleu) {
            fprintf(fichier, "B %d\nR %d\n", tresorBleu, tresorRouge);
        } else {
            fprintf(fichier, "R %d\nB %d\n", tresorRouge, tresorBleu);
        }
        Personnage* chateau = monde->chateauBleu;
        Personnage* perso;
        while (chateau != NULL) {
            if (chateau->tpsProd == 0) {
                fprintf(fichier, "B c %d %d\n", chateau->y+1, chateau->x+1);
            } else if (chateau->typeProd == Seigneur) {
                fprintf(fichier, "B c %d %d s %d\n", chateau->y+1, chateau->x+1, 6-chateau->tpsProd);
            } else if (chateau->typeProd == Guerrier) {
                fprintf(fichier, "B c %d %d g %d\n", chateau->y+1, chateau->x+1, 4-chateau->tpsProd);
            } else {
                fprintf(fichier, "B c %d %d m %d\n", chateau->y+1, chateau->x+1, 2-chateau->tpsProd);
            }
            perso = chateau->next;
            while (perso != NULL) {
                if (perso->nom == Seigneur) {
                    fprintf(fichier, "B s %d %d %d %d\n", perso->y+1, perso->x+1, perso->yDest+1, perso->xDest+1);
                } else if (perso->nom == Guerrier) {
                    fprintf(fichier, "B g %d %d %d %d\n", perso->y+1, perso->x+1, perso->yDest+1, perso->xDest+1);
                } else if (perso->nom == Manant) {
                    fprintf(fichier, "B m %d %d %d %d\n", perso->y+1, perso->x+1, perso->yDest+1, perso->xDest+1);
                }
                perso = perso->next;
            }
            chateau = chateau->vNext;
        }
        chateau = monde->chateauRouge;
        while (chateau != NULL) {
            if (chateau->tpsProd == 0) {
                fprintf(fichier, "R c %d %d\n", chateau->y+1, chateau->x+1);
            } else if (chateau->typeProd == Seigneur) {
                fprintf(fichier, "R c %d %d s %d\n", chateau->y+1, chateau->x+1, 6-chateau->tpsProd);
            } else if (chateau->typeProd == Guerrier) {
                fprintf(fichier, "R c %d %d g %d\n", chateau->y+1, chateau->x+1, 4-chateau->tpsProd);
            } else {
                fprintf(fichier, "R c %d %d m %d\n", chateau->y+1, chateau->x+1, 2-chateau->tpsProd);
            }
            perso = chateau->next;
            while (perso != NULL) {
                if (perso->nom == Seigneur) {
                    fprintf(fichier, "R s %d %d %d %d\n", perso->y+1, perso->x+1, perso->yDest+1, perso->xDest+1);
                } else if (perso->nom == Guerrier) {
                    fprintf(fichier, "R g %d %d %d %d\n", perso->y+1, perso->x+1, perso->yDest+1, perso->xDest+1);
                } else if (perso->nom == Manant) {
                    fprintf(fichier, "R m %d %d %d %d\n", perso->y+1, perso->x+1, perso->yDest+1, perso->xDest+1);
                }
                perso = perso->next;
            }
            chateau = chateau->vNext;
        }
        printf("Fichier sauvegardé\n\n");
        fclose(fichier);
    } else {
        printf("erreur");
    }
}

Monde* chargeFile(FILE* fichier, int* debut, int* tresorBleu, int* tresorRouge){
    Monde* monde = malloc(sizeof(Monde));
    monde->plateau = malloc(8*sizeof(Case**));
    for(int i = 0; i<8; i++){
        monde->plateau[i] = malloc(8*sizeof(Case*));
        for (int j = 0; j<8; j++){
            monde->plateau[i][j] = malloc(sizeof(Case));
            monde->plateau[i][j]->perso = NULL;
            monde->plateau[i][j]->chateau = NULL;
        }
    }
    fseek(fichier, 5, SEEK_SET);
    char c = fgetc(fichier);
    if (c == 'B') {
        *debut = 0;
        fseek(fichier, 2, SEEK_CUR);
        fscanf(fichier, "%d", tresorBleu);
        fseek(fichier, 3, SEEK_CUR);
        fscanf(fichier, "%d", tresorRouge);
    } else {
        *debut = 1;
        fseek(fichier, 2, SEEK_CUR);
        fscanf(fichier, "%d", tresorRouge);
        fseek(fichier, 3, SEEK_CUR);
        fscanf(fichier, "%d", tresorBleu);
    }
    while (c != EOF) {
        c = fgetc(fichier);
        if (c == 'B'){

        }
    }
    return NULL;
}

