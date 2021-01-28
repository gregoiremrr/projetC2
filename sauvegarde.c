#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sauvegarde.h"
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
        printf("Erreur lors de la creation du fichier de sauvegarde...");
    }
}

int lenFichier(FILE* fichier){
    char a = 'a', ligne[100];
    int len = 0;
    while (a != EOF) {
        fscanf(fichier, " %[^\n]s\n", ligne);
        fseek(fichier, 2, SEEK_CUR);
        a = fgetc(fichier);
        fseek(fichier, -3, SEEK_CUR);
        len++;
    }
    return len;
}

Monde* chargeFile(FILE* fichier, int* tresorBleu, int* tresorRouge, int* debut){
    int len = lenFichier(fichier);printf("ok0\n");
    rewind(fichier);
    char** lignes = malloc((len)*sizeof(char*));
    for (int i = 0; i<len; i++) {
        lignes[i] = malloc(100*sizeof(char));
    }printf("ok1\n");
    Personnage* mainBleu = NULL,* mainRouge = NULL;
    printf("ok2\n");
    Personnage** personnages = malloc((len-3)*sizeof(Personnage*));
    for (int i = 0; i<len-3; i++) {
        personnages[i] = malloc(sizeof(Personnage));
    }
    printf("ok3\n");
    fscanf(fichier, " %[^\n]s\n", lignes[0]);
    printf("%s\n", lignes[0]);
    fscanf(fichier, " %[^\n]s\n", lignes[1]);
    printf("%s\n", lignes[1]);
    fscanf(fichier, " %[^\n]s\n", lignes[2]);
    printf("%s\n", lignes[2]);
    
    for (int j = 3; j < len; j++) {
        fscanf(fichier, " %[^\n]s\n", lignes[j]);
        printf("%s\n", lignes[j]);
    }printf("ok5\n");
    
    for (int i = 3; i<len; i++) {printf("ok6\n");
        int j = i - 3;
        printf("ok\n");
        printf("%s", lignes[i]);
        if (charEstDans('R', lignes[i])) {
            personnages[j]->couleur = Rouge;
            if (charEstDans('c', lignes[i])) {
                personnages[j]->nom = Chateau;
                personnages[j]->previous = NULL;
                personnages[j]->next = NULL;
                personnages[j]->vPrevious = mainRouge;
                personnages[j]->vNext = NULL;
                mainRouge = personnages[j];printf("ok7\n");
                if (personnages[j]->vPrevious != NULL) {
                    personnages[j]->vPrevious->vNext = personnages[j];
                }
                if (charEstDans('s', lignes[i])) {
                    personnages[j]->typeProd = Seigneur;
                    personnages[j]->tpsProd = 6 - atoi(&lignes[i][strlen(lignes[i])-1]);
                } else if (charEstDans('g', lignes[i])) {
                    personnages[j]->typeProd = Guerrier;
                    personnages[j]->tpsProd = 4 - atoi(lignes[i]+strlen(lignes[i])-1);
                } else if (charEstDans('m', lignes[i])){
                    personnages[j]->typeProd = Manant;
                    personnages[j]->tpsProd = 2 - atoi(lignes[i]+strlen(lignes[i])-1);
                } else {
                    personnages[j]->typeProd = nul;
                    personnages[j]->tpsProd = 0;
                }
                personnages[j]->num = incrementAndGet(personnages[j]);
                personnages[j]->x = atoi(lignes[i]+4);printf("ok8\n");
                personnages[j]->xDest = personnages[j]->x;
                personnages[j]->y = atoi(lignes[i]+6);
                personnages[j]->yDest = personnages[j]->y;
            } else if (charEstDans('s', lignes[i])) {
                personnages[j]->nom = Seigneur;
                personnages[j]->x = atoi(lignes[i]+4);
                personnages[j]->y =  atoi(lignes[i]+6);printf("ok9\n");
                personnages[j]->xDest = atoi(lignes[i]+8);
                personnages[j]->yDest = atoi(lignes[i]+10);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainRouge;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;printf("ok10\n");
            } else if (charEstDans('g', lignes[i])) {
                personnages[j]->nom = Guerrier;
                personnages[j]->x = atoi(lignes[i]+4);
                personnages[j]->y =  atoi(lignes[i]+6);
                personnages[j]->xDest = atoi(lignes[i]+8);
                personnages[j]->yDest = atoi(lignes[i]+10);printf("ok11\n");
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainRouge;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }printf("ok1\n");
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
            } else {
                personnages[j]->nom = Manant;printf("ok12\n");
                personnages[j]->x = atoi(lignes[i]+4);
                personnages[j]->y =  atoi(lignes[i]+6);
                personnages[j]->xDest = atoi(lignes[i]+8);
                char* a = lignes[i]+8;
                while (*a != 32) {
                    a++;
                }printf("ok1\n");
                a++;
                personnages[j]->yDest = atoi(a);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainRouge;printf("ok13\n");
                while (persoInter->next){
                    persoInter = persoInter->next;
                    printf("voila\n");
                }
                personnages[j]->previous = persoInter;printf("ok14\n");
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
            }
        } else {
            printf("ok\n");
            personnages[j]->couleur = Bleu;printf("ok15\n");
            if (charEstDans('c', lignes[i])) {
                personnages[j]->nom = Chateau;printf("ok16\n");
                personnages[j]->previous = NULL;
                personnages[j]->next = NULL;
                personnages[j]->vPrevious = mainBleu;
                personnages[j]->vNext = NULL;printf("ok17\n");
                mainBleu = personnages[j];
                if (personnages[j]->vPrevious != NULL) {
                    personnages[j]->vPrevious->vNext = personnages[j];
                }
                if (charEstDans('s', lignes[i])) {printf("ok18\n");
                    personnages[j]->typeProd = Seigneur;
                    personnages[j]->tpsProd = 6 - atoi(&lignes[i][strlen(lignes[i])-1]);
                } else if (charEstDans('g', lignes[i])) {
                    personnages[j]->typeProd = Guerrier;printf("ok18\n");
                    personnages[j]->tpsProd = 4 - atoi(lignes[i]+strlen(lignes[i])-1);
                } else if (charEstDans('m', lignes[i])){printf("ok19\n");
                    personnages[j]->typeProd = Manant;
                    personnages[j]->tpsProd = 2 - atoi(lignes[i]+strlen(lignes[i])-1);
                } else {printf("ok20\n");
                    personnages[j]->typeProd = nul;
                    personnages[j]->tpsProd = 0;
                }printf("ok21\n");
                personnages[j]->num = incrementAndGet(personnages[j]);
                personnages[j]->x = atoi(lignes[i]+4);
                personnages[j]->xDest = personnages[j]->x;
                personnages[j]->y = atoi(lignes[i]+6);printf("ok22\n");
                personnages[j]->yDest = personnages[j]->y;
            } else if (charEstDans('s', lignes[i])) {
                personnages[j]->nom = Seigneur;
                personnages[j]->x = atoi(lignes[i]+4);printf("ok23\n");
                personnages[j]->y =  atoi(lignes[i]+6);
                personnages[j]->xDest = atoi(lignes[i]+8);
                personnages[j]->yDest = atoi(lignes[i]+10);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){printf("ok24\n");
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;printf("ok25\n");
            } else if (charEstDans('g', lignes[i])) {
                personnages[j]->nom = Guerrier;
                personnages[j]->x = atoi(lignes[i]+4);
                personnages[j]->y =  atoi(lignes[i]+6);
                personnages[j]->xDest = atoi(lignes[i]+8);printf("ok26\n");
                personnages[j]->yDest = atoi(lignes[i]+10);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }printf("ok27\n");
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;printf("ok28\n");
            } else {
                printf("here");
                personnages[j]->nom = Manant;
                personnages[j]->x = atoi(lignes[i]+4);
                personnages[j]->y =  atoi(lignes[i]+6);
                personnages[j]->xDest = atoi(lignes[i]+8);printf("ok29\n");
                char* a = lignes[i]+8;
                while (*a != 32) {
                    a++;
                }printf("ok30\n");
                a++;
                personnages[j]->yDest = atoi(a);
                personnages[j]->num = incrementAndGet(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }printf("ok31\n");
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
            }printf("ok32\n");
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
    }printf("ok33\n");
    for(int k = 0; k < len - 3 ; k++) {
        printf("%d\n", k);
        if (personnages[k]->nom == Chateau) {
            printf("haha\n");
            monde->plateau[personnages[k]->x][personnages[k]->y]->chateau = personnages[k];
        printf("ok34\n");} else {printf("ok35\n");
            if (monde->plateau[personnages[k]->x][personnages[k]->y]->perso == NULL) {
                monde->plateau[personnages[k]->x][personnages[k]->y]->perso = personnages[k];
            } else {printf("ok36\n");
                Personnage* persoInterm = monde->plateau[personnages[k]->x][personnages[k]->y]->perso;
                while (persoInterm->vNext != NULL) {
                    persoInterm = persoInterm->vNext;
                }
                personnages[k]->vPrevious = persoInterm;
                persoInterm->vNext = personnages[k];
            }printf("ok37\n");
        }
    }
    Personnage* chateauInter = mainRouge;
    while (chateauInter->vPrevious) {
        chateauInter = chateauInter->vPrevious;
    }printf("ok38\n");
    monde->chateauRouge = chateauInter;
    chateauInter = mainBleu;
    while (chateauInter->vPrevious) {
        chateauInter = chateauInter->vPrevious;
    }printf("ok39\n");
    monde->chateauBleu = chateauInter;
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