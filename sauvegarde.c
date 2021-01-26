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
    fseek(fichier, 4, SEEK_SET);
    int i =0;
    char C;
    int tres;
    c = fgetc(fichier);
    while (c != EOF && i < 2){
        debutLigne = ftell(fichier);
        printf("%d\n", debutLigne);
        while (c != '\n') {
            c = fgetc(fichier);
        }
        finLigne = ftell(fichier);
        printf("%d\n", finLigne)
        fseek(fichier, debutLigne, SEEK_SET);
        char* ligne = malloc(sizeof(char)*(finLigne-debutLigne));
        ligne = fgets(ligne, finLigne-debutLigne, fichier);
        sscanf(line, "%c %d", C, tres )
        if (C == 'R') {
            tresorRouge = tres;
        } else {
            tresorBleu = tres;
        }
        c = fgetc(fichier);
        i++;
    }
    if (C == 'R')
        debut = 0;
    else 
        debut =1;
    while (c != EOF){
        int x;
        int y;
        int xDest;
        int yDest;
        char type;
        char typePro;
        int tps;
        debutLigne = ftell(fichier);
        printf("%d\n", debutLigne);
        while(c != '\n')
            c = fgetc(fichier);
        finLigne = ftell(fichier);
        printf("%d\n", finLigne);
        fseek(fichier, debutLigne, SEEK_SET);
        char* ligne = malloc(sizeof(char)*(finLigne-debutLigne));
        ligne = fgets(ligne, finLigne-debutLigne, fichier);
        sscanf(ligne,"%c %c %d %d %c %d", C, type, x, y,typePro, tps);
        //récupération du 1er chateau
        while (C == 'B'){
            monde->chateauBleu = malloc(sizeof(Personnage));
            monde->chateauBleu->nom = Chateau;
            monde->chateauBleu->x = x;
            monde->chateauBleu->y = y;
            monde->chateauBleu->xDest = x;
            monde->chateauBleu->yDest = y;
            monde->chateauBleu->couleur = Bleu;
            if (typePro == 's'){
                monde->chateauBleu->typeProd = Seigneur;
                monde->chateauBleu->tpsProd = 6-tps;
            } else if(typePro == 'g'{
                monde->chateauBleu->typeProd = Guerrier;
                monde->chateauBleu->tpsProd = 4-tps;
            } else if (typePro == 'm'{
                monde->chateauBleu->typeProd = Manant;
                monde->chateauBleu->tpsProd = 1-tps;
            } else {
                monde->chateauBleu->typeProd = nul;
                monde->chateauBleu->tpsProd = 0;
            }
            monde->chateauBleu->previous = NULL;
            monde->chateauBleu->vNext = NULL;
            monde->chateauBleu->vPrevious = NULL;
            monde->chateauBleu->coupDeProd = 30;
            monde->chateauBleu->num = incrementAndGet(monde->chateauBleu);
            monde->plateau[x][y]->chateau = monde->chateauBleu;
            //récupération du reste des personnages de la même couleur
            Personnage * chateauMain = monde->chateauBleu;
            c = fgetc(fichier);
            debutLigne = ftell(fichier);
            printf("%d\n", debutLigne);
            while(c != '\n')
                c = fgetc(fichier);
            finLigne = ftell(fichier);
            printf("%d\n", finLigne);
            fseek(fichier, debutLigne, SEEK_SET);
            char* ligne = malloc(sizeof(char)*(finLigne-debutLigne));
            ligne = fgets(ligne, finLigne-debutLigne, fichier);
            if (ligne[2] == 'c' ) {
                sscanf(ligne,"%c %c %d %d %c %d", C, type, x, y,typePro, tps);
                Personnage* nvChateau = malloc(sizeof(Personnage));
                nvChateau->nom = Chateau;
                nvChateau->couleur = Bleu;
                nvChateau->x = x;
                nvChateau->y = y;
                nvChateau->xDest = x;
                nvChateau->yDest = y;
                nvChateau->coupDeProd = 30;
                nvChateau->vNext = NULL;
                Personnage* chateau = monde->chateauBleu;
                while(chateau->vNext != NULL){
                    chateau = chateau->vNext;
                }
                nvChateau->vPrevious = chateau;
                chateau->vNext = nvChateau;
                chateau->vNext = nvChateau;
                if (typePro == 's'){
                nvChateau->typeProd = Seigneur;
                nvchateau->tpsProd = 6-tps;
            } else if(typePro == 'g'{
                nvChateau->typeProd = Guerrier;
                nvchateau->tpsProd = 4-tps;
            } else if (typePro == 'm'{
                nvChateau->typeProd = Manant;
                nvChateau->tpsProd = 1-tps;
            } else {
                nvChateau->typeProd = nul;
                nvChateau->tpsProd = 0;
            }
                nvChateau->next = NULL;
                nvChateau->previous = NULL;
                nvChateau->num = incrementAndGet(nvChateau);
                monde->plateau[x][y]->chateau = nvChateau;
                chateauMain = nvChateau;
            } else if(ligne[2] = 's') {
                sscanf(ligne, "%c %c %d %d %d %d", C, type, x, y, xDest, yDest);
                Personnage* nvPerso = malloc(sizeof(Personnage));
                nvPerso->nom = Seigneur;
                nvPerso->couleur = Bleu;
                nvPerso->x = x;
                nvPerso->y = y;
                nvPerso->xDest = xDest;
                nvPerso->yDest = yDest;
                Personnage* prev = chateauMain;
                while (prev->next){
                    prev = prev->next;
                }
                nvPerso->previous = prev;
                nvPerso->next =NULL;
                nvPerso->previous->next = nvPerso;
                if (monde->plateau[x][y]->perso != NULL) {
                    Personnage *persoInter = monde->plateau[x][y]->perso;
                    while(persoInter->next != NULL) {
                         persoInter = persoInter->next;
                    }
                    nvPerso->vPrevious = persoInter;
                    nvPerso->vNext = NULL;
                    persoInter->vNext = nvPerso;
                } else 
                    monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
                nvPerso->num = incrementAndGet(nvPerso);
                nvPerso->coupDeProd = 20;
            }else if (ligne[2] = 'g') {
                sscanf(ligne, "%c %c %d %d %d %d", C, type, x, y, xDest, yDest);
                Personnage* nvPerso = malloc(sizeof(Personnage));
                nvPerso->nom = Guerrier;
                nvPerso->couleur = Bleu;
                nvPerso->x = x;
                nvPerso->y = y;
                nvPerso->xDest = xDest;
                nvPerso->yDest = yDest;
                Personnage* prev = chateauMain;
                while (prev->next){
                    prev = prev->next;
                }
                nvPerso->previous = prev;
                nvPerso->next =NULL;
                nvPerso->previous->next = nvPerso;
                if (monde->plateau[x][y]->perso != NULL) {
                    Personnage *persoInter = monde->plateau[x][y]->perso;
                    while(persoInter->next != NULL) {
                         persoInter = persoInter->next;
                    }
                    nvPerso->vPrevious = persoInter;
                    nvPerso->vNext = NULL;
                    persoInter->vNext = nvPerso;
                } else 
                    monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
                nvPerso->num = incrementAndGet(nvPerso);
                nvPerso->coupDeProd = 5;
            } else if(ligne[2] = 'm'){
                sscanf(ligne, "%c %c %d %d %d %d", C, type, x, y, xDest, yDest);
                Personnage* nvPerso = malloc(sizeof(Personnage));
                nvPerso->nom = Manant;
                nvPerso->couleur = Bleu;
                nvPerso->x = x;
                nvPerso->y = y;
                nvPerso->xDest = xDest;
                nvPerso->yDest = yDest;
                Personnage* prev = chateauMain;
                while (prev->next){
                    prev = prev->next;
                }
                nvPerso->previous = prev;
                nvPerso->next =NULL;
                nvPerso->previous->next = nvPerso;
                if (monde->plateau[x][y]->perso != NULL) {
                    Personnage *persoInter = monde->plateau[x][y]->perso;
                    while(persoInter->next != NULL) {
                        persoInter = persoInter->next;
                    }
                    nvPerso->vPrevious = persoInter;
                    nvPerso->vNext = NULL;
                    persoInter->vNext = nvPerso;
                } else 
                    monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
                nvPerso->num = incrementAndGet(nvPerso);
                nvPerso->coupDeProd = 20;
            }
            c = fgetc(fichier);
        } 
        while (C == 'R'){
            monde->chateauRouge = malloc(sizeof(Personnage));
            monde->chateauRouge->nom = Chateau;
            monde->chateauRouge->x = x;
            monde->chateauRouge->y = y;
            monde->chateauRouge->xDest = x;
            monde->chateauRouge->yDest = y;
            monde->chateauRouge->couleur = Rouge;
            if (typePro == 's'){
                monde->chateauRouge->typeProd = Seigneur;
                monde->chateauRouge->tpsProd = 6-tps;
            } else if(typePro == 'g'{
                monde->chateauRouge->typeProd = Guerrier;
                monde->chateauRouge->tpsProd = 4-tps;
            } else if (typePro == 'm'{
                monde->chateauRouge->typeProd = Manant;
                monde->chateauRouge->tpsProd = 1-tps;
            } else {
                monde->chateauRouge->typeProd = nul;
                monde->chateauRouge->tpsProd = 0;
            }
            monde->chateauRouge->previous = NULL;
            monde->chateauRouge->vNext = NULL;
            monde->chateauRouge->vPrevious = NULL;
            monde->chateauRouge->coupDeProd = 30;
            monde->chateauRouge->num = incrementAndGet(monde->chateauRouge);
            monde->plateau[x][y]->chateau = monde->chateauRouge;
        }
    }

    

}
    


