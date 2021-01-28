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

int lenFichier(FILE* fichier){
    char a = 'a', ligne[100];
    int len = 0;
    while (a != EOF) {
        fscanf(fichier, " %[^\n]s\n", ligne);
        fseek(fichier, 2, SEEK_CUR);
        printf("%s\n", ligne);
        a = fgetc(fichier);
        printf("'%c'\n", a);
        fseek(fichier, -3, SEEK_CUR);
        len++;
    }
    return len;
}

Monde* chargeFile(FILE* fichier, int* tresorBleu, int* tresorRouge, int* debut){
    int len = lenFichier(fichier);
    char** lignes = malloc((len)*sizeof(char*));
    for (int i = 0; i<len; i++) {
        lignes = malloc(100*sizeof(char));
    }
    Personnage* mainBleu = NULL,* mainRouge = NULL;

    Personnage** personnages = malloc(len*sizeof(Personnage*));
    for (int i = 0; i<len-3; i++) {
        personnages[i] = malloc(sizeof(Personnage));
    }
    
    fscanf(fichier, " %[^\n]s\n", lignes[0]);
    fscanf(fichier, " %[^\n]s\n", lignes[1]);
    fscanf(fichier, " %[^\n]s\n", lignes[2]);
    
    int j = 3;
    while (j<len) {
        fscanf(fichier, " %[^\n]s\n", lignes[j]);
        j++;
    }
    
    for (i = 3; i<len; i++) {
        j = i - 3;
        if (charEstDans('R', lignes[i])) {
            personnages[j]->couleur = Rouge;
            if (charEstDans('c', lignes[i])) {
                personnages[j]->nom = Chateau;
                personnages[j]->previous = NULL;
                personnages[j]->next = NULL;
                personnages[j]->vPrevious = mainRouge;
                personnages[j]->vNext = NULL;
                mainRouge = personnages[j];
                personnages[j]->vPrevious->vNext = personnages[j];
                if (charEstDans('s', lignes[i])) {
                    personnages[j]->typeProd = Seigneur;
                    personnages[j]->tpsProd = 6 - atoi(&lignes[i][strlen(ligne[i])-1]);
                } else if (charEstDans('g', lignes[i])) {
                    personnages[j]->typeProd = Guerrier;
                    personnages[j]->tpsProd = 4 - atoi(lignes[i]+strlen(ligne[i])-1);
                } else if (charEstDans('', lignes[i])){
                    personnages[j]->typeProd = Manant;
                    personnages[j]->tpsProd = 2 - atoi(lignes[i]+strlen(ligne[i])-1);
                } else {
                    personnages[j]->typeProd = nul;
                    personnages[j]->tpsProd = 0;
                }
                personnages[j]->num = incrementAndGet(personnages[j]);
                personnages[j]->x = atoi(ligne[i]+4);
                personnages[j]->xDest = personnages[j]->x;
                personnages[j]->y = atoi(ligne[i]+6);
                personnages[j]->yDest = personnages[j]->y;
            } else if (charEstDans('s', lignes[i])) {
                personnages[j]->nom = Seigneur;
                personnages[j]->x = atoi(ligne[i]+4);
                personnages[j]->y =  atoi(ligne[i]+6);
                personnages[j]->xDest = atoi(ligne[i]+8);
                personnages[j]->yDest = atoi(ligne[i]+10);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainRouge;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[i];
                personnages[j]->next = NULL;
            } else if (charEstDans('g', lignes[i])) {
                personnages[j]->nom = Guerrier;
                personnages[j]->x = atoi(ligne[i]+4);
                personnages[j]->y =  atoi(ligne[i]+6);
                personnages[j]->xDest = atoi(ligne[i]+8);
                personnages[j]->yDest = atoi(ligne[i]+10);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainRouge;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[i];
                personnages[j]->next = NULL;
            } else {
                personnages[j]->nom = Manant;
                personnages[j]->x = atoi(ligne[i]+4);
                personnages[j]->y =  atoi(ligne[i]+6);
                personnages[j]->xDest = atoi(ligne[i]+8);
                char* a = ligne[i]+8;
                while (*a != 32) {
                    a++;
                }
                a++;
                personnages[j]->yDest = atoi(a);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainRouge;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[i];
                personnages[j]->next = NULL;
            }
        } else {
            personnages[j]->couleur = Bleu;
            if (charEstDans('c', lignes[i])) {
                personnages[j]->nom = Chateau;
                personnages[j]->previous = NULL;
                personnages[j]->next = NULL;
                personnages[j]->vPrevious = mainBleu;
                personnages[j]->vNext = NULL;
                mainBleu = personnages[j];
                personnages[j]->vPrevious->vNext = personnages[j];
                if (charEstDans('s', lignes[i])) {
                    personnages[j]->typeProd = Seigneur;
                    personnages[j]->tpsProd = 6 - atoi(&lignes[i][strlen(ligne[i])-1]);
                } else if (charEstDans('g', lignes[i])) {
                    personnages[j]->typeProd = Guerrier;
                    personnages[j]->tpsProd = 4 - atoi(lignes[i]+strlen(ligne[i])-1);
                } else if (charEstDans('', lignes[i])){
                    personnages[j]->typeProd = Manant;
                    personnages[j]->tpsProd = 2 - atoi(lignes[i]+strlen(ligne[i])-1);
                } else {
                    personnages[j]->typeProd = nul;
                    personnages[j]->tpsProd = 0;
                }
                personnages[j]->num = incrementAndGet(personnages[j]);
                personnages[j]->x = atoi(ligne[i]+4);
                personnages[j]->xDest = personnages[j]->x;
                personnages[j]->y = atoi(ligne[i]+6);
                personnages[j]->yDest = personnages[j]->y;
            } else if (charEstDans('s', lignes[i])) {
                personnages[j]->nom = Seigneur;
                personnages[j]->x = atoi(ligne[i]+4);
                personnages[j]->y =  atoi(ligne[i]+6);
                personnages[j]->xDest = atoi(ligne[i]+8);
                personnages[j]->yDest = atoi(ligne[i]+10);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[i];
                personnages[j]->next = NULL;
            } else if (charEstDans('g', lignes[i])) {
                personnages[j]->nom = Guerrier;
                personnages[j]->x = atoi(ligne[i]+4);
                personnages[j]->y =  atoi(ligne[i]+6);
                personnages[j]->xDest = atoi(ligne[i]+8);
                personnages[j]->yDest = atoi(ligne[i]+10);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[i];
                personnages[j]->next = NULL;
            } else {
                personnages[j]->nom = Manant;
                personnages[j]->x = atoi(ligne[i]+4);
                personnages[j]->y =  atoi(ligne[i]+6);
                personnages[j]->xDest = atoi(ligne[i]+8);
                char* a = ligne[i]+8;
                while (*a != 32) {
                    a++;
                }
                a++;
                personnages[j]->yDest = atoi(a);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[i];
                personnages[j]->next = NULL;
            }
        }
    }
    Monde* monde = malloc(sizeof(Monde));
    monde->plateau = malloc(8 * sizeof(Case **));
    for (int i = 0; i < 8; i++) {
        monde->plateau[i] = malloc(8 * sizeof(Case*));
        for (int j = 0; j < 8; j++) {
            monde->plateau[i][j] = malloc(sizeof(Case));
            monde->plateau[i][j]->perso = NULL;
            monde->plateau[i][j]->chateau = NULL;
        }
    }
    for(int k = 0; k < len - 3 ; k++) {
        if (personnages[k]->nom == Chateau) {
            monde->plateau[personnages[k]->x][personnages[k]->y]->chateau = personnages[k];
        } else {
            if (monde->plateau[personnages[k]->x][personnages[k]->y]->perso == NULL) {
                monde->plateau[personnages[k]->x][personnages[k]->y]->perso = personnages[k];
            } else {
                Personnage* persoInterm = monde->plateau[personnages[k]->x][personnages[k]->y]->perso;
                while (persoInterm->next != NULL) {
                    persoInterm = persoInterm->next;
                }
                personnages[k]->vPrevious = persoInterm;
                persoInterm->vNext = personnages[k];
            }
        }
    }
    return monde;
}

int charEstDans(char c, char* str) {
    int i = 0;
    while (str[i] != '\0' && str[i] != c) {
        i++;
    }
    if (str[i] == '\0') {
        return 0;
    }
    return 1;
}