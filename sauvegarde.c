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
    c = fgetc(fichier);
    while (c != EOF) {
        if (c == 'B'){
            fseek(fichier, 4, SEEK_CUR);
            c = fgetc(fichier);
            monde->chateauBleu = malloc(sizeof(Personnage));
            monde->chateauBleu->nom = Chateau;
            monde->chateauBleu->x = atoi(&c);
            fseek(fichier, 2, SEEK_CUR);
            c = fgetc(fichier);
            monde->chateauBleu->y = atoi(&c);
            fseek(fichier, 2, SEEK_CUR);
            c = fgetc(fichier);
            if (c == 'm') {
                monde->chateauBleu->typeProd = Manant;
                fseek(fichier, 2, SEEK_CUR);
                c = fgetc(fichier);
                monde->chateauBleu->tpsProd = 2 - atoi(&c);
                c = fgetc(fichier);
            } else if (c == 's') {
                monde->chateauBleu->typeProd = Seigneur;
                fseek(fichier, 2, SEEK_CUR);
                c = fgetc(fichier);
                monde->chateauBleu->tpsProd = 6 - atoi(&c);
                c = fgetc(fichier);
            } else if (c == 'g') {
                monde->chateauBleu->typeProd = Guerrier;
                fseek(fichier, 2, SEEK_CUR);
                c = fgetc(fichier);
                monde->chateauBleu->tpsProd = 4 - atoi(&c);
                c = fgetc(fichier);
            } else {
                monde->chateauBleu->typeProd = nul;
                monde->chateauBleu->tpsProd = 0;
            }
            monde->chateauBleu->xDest = monde->chateauBleu->x;
            monde->chateauBleu->yDest = monde->chateauBleu->x;
            monde->chateauBleu->previous = NULL;
            monde->chateauBleu->vNext = NULL;
            monde->chateauBleu->vPrevious = NULL;
            monde->chateauBleu->coupDeProd = 30;
            monde->chateauBleu->couleur = Bleu;
            monde->chateauBleu->num = incrementAndGet(monde->chateauBleu);
            monde->plateau[monde->chateauBleu->x][monde->chateauBleu->y]->chateau = monde->chateauBleu;
            c = fgetc(fichier);
        } else if (c == 'R') {
            fseek(fichier, 4, SEEK_CUR);
            c = fgetc(fichier);
            monde->chateauRouge = malloc(sizeof(Personnage));
            monde->chateauRouge->nom = Chateau;
            monde->chateauRouge->x = atoi(&c);
            fseek(fichier, 2, SEEK_CUR);
            c = fgetc(fichier);
            monde->chateauRouge->y = atoi(&c);
            fseek(fichier, 2, SEEK_CUR);
            c = fgetc(fichier);
            if (c == 'm') {
                monde->chateauRouge->typeProd = Manant;
                fseek(fichier, 2, SEEK_CUR);
                c = fgetc(fichier);
                monde->chateauRouge->tpsProd = 2 - atoi(&c);
                c = fgetc(fichier);
            } else if (c == 's') {
                monde->chateauRouge->typeProd = Seigneur;
                fseek(fichier, 2, SEEK_CUR);
                c = fgetc(fichier);
                monde->chateauRouge->tpsProd = 6 - atoi(&c);
                c = fgetc(fichier);
            } else if (c == 'g') {
                monde->chateauRouge->typeProd = Guerrier;
                fseek(fichier, 2, SEEK_CUR);
                c = fgetc(fichier);
                monde->chateauRouge->tpsProd = 4 - atoi(&c);
                c = fgetc(fichier);
            } else {
                monde->chateauRouge->typeProd = nul;
                monde->chateauRouge->tpsProd = 0;
            }
            monde->chateauRouge->xDest = monde->chateauRouge->x;
            monde->chateauRouge->yDest = monde->chateauRouge->x;
            monde->chateauRouge->previous = NULL;
            monde->chateauRouge->vNext = NULL;
            monde->chateauRouge->vPrevious = NULL;
            monde->chateauRouge->coupDeProd = 30;
            monde->chateauRouge->couleur = Rouge;
            monde->chateauRouge->num = incrementAndGet(monde->chateauRouge);
            monde->plateau[monde->chateauRouge->x][monde->chateauRouge->y]->chateau = monde->chateauRouge;
            c = fgetc(fichier);
        }
        if (c == 'B') {
            fseek(fichier, 2, SEEK_CUR);
            c = fgetc(fichier);
            if (c =='c') { 
                    Personnage *nvChateau = malloc(sizeof(Personnage));
                    nvChateau->nom = Chateau;
                    nvChateau->couleur = Bleu;
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvChateau->x = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvChateau->y = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    if (c == 'm') {
                        nvChateau->typeProd = Manant;
                        fseek(fichier, 2, SEEK_CUR);
                        c = fgetc(fichier);
                        nvChateau->tpsProd = 2 - atoi(&c);
                        c = fgetc(fichier);
                    } else if (c == 's') {
                        nvChateau->typeProd = Seigneur;
                        fseek(fichier, 2, SEEK_CUR);
                        c = fgetc(fichier);
                        nvChateau->tpsProd = 6 - atoi(&c);
                        c = fgetc(fichier);
                    } else if (c == 'g') {
                        nvChateau->typeProd = Guerrier;
                        fseek(fichier, 2, SEEK_CUR);
                        c = fgetc(fichier);
                        nvChateau->tpsProd = 4 - atoi(&c);
                        c = fgetc(fichier);
                    } else {
                        nvChateau->typeProd = nul;
                        nvChateau->tpsProd = 0;
                    }
                    nvChateau->xDest = nvChateau->x;
                    nvChateau->yDest = nvChateau->x;
                    nvChateau->previous = NULL;
                    nvChateau->vNext = NULL;
                    nvChateau->coupDeProd = 30;
                    nvChateau->couleur = Bleu;
                    Personnage* chateau = monde->chateauBleu;
                    while(chateau->vNext != NULL){
                        chateau = chateau->vNext;
                    }
                    nvChateau->vPrevious = chateau;
                    chateau->vNext = nvChateau;
                    nvChateau->num = incrementAndGet(nvChateau);
                    monde->plateau[nvChateau->x][nvChateau->y]->chateau = nvChateau;
                    
                } else if(c == 's') {
                    Personnage* nvPerso = malloc(sizeof(Personnage));
                    nvPerso->nom = Seigneur;
                    nvPerso->couleur = Bleu;
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->x = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->y = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->xDest = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->yDest = atoi(&c);
                    nvPerso->couleur = Bleu;
                    nvPerso->num = incrementAndGet(nvPerso);
                    nvPerso->coupDeProd = 20;
                    Personnage* prev = monde->chateauBleu;
                    while (prev->next){
                        prev = prev->next;
                    }
                    nvPerso->previous = prev;
                    nvPerso->next =NULL;
                    nvPerso->previous->next = nvPerso;
                    if (monde->plateau[nvPerso->x][nvPerso->y]->perso != NULL) {
                        Personnage *persoInter = monde->plateau[nvPerso->x][nvPerso->y]->perso;
                        while(persoInter->next != NULL) {
                            persoInter = persoInter->next;
                        }
                        nvPerso->vPrevious = persoInter;
                        nvPerso->vNext = NULL;
                        persoInter->vNext = nvPerso;
                    } else 
                        monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
                    
                } else if (c == 'g') {
                    Personnage* nvPerso = malloc(sizeof(Personnage));
                    nvPerso->nom = Guerrier;
                    nvPerso->couleur = Bleu;
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->x = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->y = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->xDest = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->yDest = atoi(&c);
                    nvPerso->couleur = Bleu;
                    nvPerso->num = incrementAndGet(nvPerso);
                    nvPerso->coupDeProd = 5;
                    Personnage* prev = monde->chateauBleu;
                    while (prev->next){
                        prev = prev->next;
                    }
                    nvPerso->previous = prev;
                    nvPerso->next =NULL;
                    nvPerso->previous->next = nvPerso;
                    if (monde->plateau[nvPerso->x][nvPerso->y]->perso != NULL) {
                        Personnage *persoInter = monde->plateau[nvPerso->x][nvPerso->y]->perso;
                        while(persoInter->next != NULL) {
                            persoInter = persoInter->next;
                        }
                        nvPerso->vPrevious = persoInter;
                        nvPerso->vNext = NULL;
                        persoInter->vNext = nvPerso;
                    } else 
                        monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
                    
                } else if (c == 'm') {
                    Personnage* nvPerso = malloc(sizeof(Personnage));
                    nvPerso->nom = Manant;
                    nvPerso->couleur = Bleu;
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->x = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->y = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->xDest = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->yDest = atoi(&c);
                    nvPerso->couleur = Bleu;
                    nvPerso->num = incrementAndGet(nvPerso);
                    nvPerso->coupDeProd = 1;
                    Personnage* prev = monde->chateauBleu;
                    while (prev->next){
                        prev = prev->next;
                    }
                    nvPerso->previous = prev;
                    nvPerso->next =NULL;
                    nvPerso->previous->next = nvPerso;
                    if (monde->plateau[nvPerso->x][nvPerso->y]->perso != NULL) {
                        Personnage *persoInter = monde->plateau[nvPerso->x][nvPerso->y]->perso;
                        while(persoInter->next != NULL) {
                            persoInter = persoInter->next;
                        }
                        nvPerso->vPrevious = persoInter;
                        nvPerso->vNext = NULL;
                        persoInter->vNext = nvPerso;
                    } else 
                        monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
                }
            
        } else if (c == 'R') {
            fseek(fichier, 2, SEEK_CUR);
            c = fgetc(fichier);
            if (c == 'c') { 
                    Personnage* nvChateau = malloc(sizeof(Personnage));
                    nvChateau->nom = Chateau;
                    nvChateau->couleur = Rouge;
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvChateau->x = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvChateau->y = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    if (c == 'm') {
                        nvChateau->typeProd = Manant;
                        fseek(fichier, 2, SEEK_CUR);
                        c = fgetc(fichier);
                        nvChateau->tpsProd = 2 - atoi(&c);
                        c = fgetc(fichier);
                    } else if (c == 's') {
                        nvChateau->typeProd = Seigneur;
                        fseek(fichier, 2, SEEK_CUR);
                        c = fgetc(fichier);
                        nvChateau->tpsProd = 6 - atoi(&c);
                        c = fgetc(fichier);
                    } else if (c == 'g') {
                        nvChateau->typeProd = Guerrier;
                        fseek(fichier, 2, SEEK_CUR);
                        c = fgetc(fichier);
                        nvChateau->tpsProd = 4 - atoi(&c);
                        c = fgetc(fichier);
                    } else {
                        nvChateau->typeProd = nul;
                        nvChateau->tpsProd = 0;
                    }
                    nvChateau->xDest = nvChateau->x;
                    nvChateau->yDest = nvChateau->x;
                    nvChateau->previous = NULL;
                    nvChateau->coupDeProd = 30;
                    nvChateau->couleur = Rouge;
                    nvChateau->vNext = NULL;
                    Personnage* chateau = monde->chateauRouge;
                    while(chateau->vNext != NULL){
                        chateau = chateau->vNext;
                    }
                    nvChateau->vPrevious = chateau;
                    chateau->vNext = nvChateau;
                    nvChateau->num = incrementAndGet(nvChateau);
                    monde->plateau[nvChateau->x][nvChateau->y]->chateau = nvChateau;
            } else if(c == 's') {
                    Personnage* nvPerso = malloc(sizeof(Personnage));
                    nvPerso->nom = Seigneur;
                    nvPerso->couleur = Rouge;
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->x = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->y = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->xDest = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->yDest = atoi(&c);
                    nvPerso->num = incrementAndGet(nvPerso);
                    nvPerso->coupDeProd = 20;
                    Personnage* prev = monde->chateauRouge;
                    while (prev->next){
                        prev = prev->next;
                    }
                    nvPerso->previous = prev;
                    nvPerso->next =NULL;
                    nvPerso->previous->next = nvPerso;
                    if (monde->plateau[nvPerso->x][nvPerso->y]->perso != NULL) {
                        Personnage *persoInter = monde->plateau[nvPerso->x][nvPerso->y]->perso;
                        while(persoInter->next != NULL) {
                            persoInter = persoInter->next;
                        }
                        nvPerso->vPrevious = persoInter;
                        nvPerso->vNext = NULL;
                        persoInter->vNext = nvPerso;
                    } else 
                        monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
            } else if (c == 'g') {
                    Personnage* nvPerso = malloc(sizeof(Personnage));
                    nvPerso->nom = Guerrier;
                    nvPerso->couleur = Rouge;
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->x = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->y = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->xDest = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->yDest = atoi(&c);
                    nvPerso->num = incrementAndGet(nvPerso);
                    nvPerso->coupDeProd = 5;
                    Personnage* prev = monde->chateauRouge;
                    while (prev->next){
                        prev = prev->next;
                    }
                    nvPerso->previous = prev;
                    nvPerso->next =NULL;
                    nvPerso->previous->next = nvPerso;
                    if (monde->plateau[nvPerso->x][nvPerso->y]->perso != NULL) {
                        Personnage *persoInter = monde->plateau[nvPerso->x][nvPerso->y]->perso;
                        while(persoInter->next != NULL) {
                            persoInter = persoInter->next;
                        }
                        nvPerso->vPrevious = persoInter;
                        nvPerso->vNext = NULL;
                        persoInter->vNext = nvPerso;
                    } else 
                        monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
            } else if (c == 'm') {
                    Personnage* nvPerso = malloc(sizeof(Personnage));
                    nvPerso->nom = Manant;
                    nvPerso->couleur = Rouge;
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->x = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->y = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->xDest = atoi(&c);
                    fseek(fichier, 2, SEEK_CUR);
                    c = fgetc(fichier);
                    nvPerso->yDest = atoi(&c);
                    nvPerso->num = incrementAndGet(nvPerso);
                    nvPerso->coupDeProd = 1;
                    Personnage* prev = monde->chateauRouge;
                    while (prev->next){
                        prev = prev->next;
                    }
                    nvPerso->previous = prev;
                    nvPerso->next =NULL;
                    nvPerso->previous->next = nvPerso;
                    if (monde->plateau[nvPerso->x][nvPerso->y]->perso != NULL) {
                        Personnage *persoInter = monde->plateau[nvPerso->x][nvPerso->y]->perso;
                        while(persoInter->next != NULL) {
                            persoInter = persoInter->next;
                        }
                        nvPerso->vPrevious = persoInter;
                        nvPerso->vNext = NULL;
                        persoInter->vNext = nvPerso;
                    } else 
                        monde->plateau[nvPerso->x][nvPerso->y]->perso = nvPerso;
            
            }
        
            
        }
        c = fgetc(fichier);
    }
    return monde;
}
    


