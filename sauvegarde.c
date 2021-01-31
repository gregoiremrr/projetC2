#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sauvegarde.h"
#include "monde.h"


void sauv(FILE* fichier, Monde* monde, Couleur couleur, int tresorRouge, int tresorBleu){
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
                fprintf(fichier, "B c %d %d\n", chateau->y, chateau->x);
            } else if (chateau->typeProd == Seigneur) {
                fprintf(fichier, "B c %d %d s %d\n", chateau->y, chateau->x, 6-chateau->tpsProd);
            } else if (chateau->typeProd == Guerrier) {
                fprintf(fichier, "B c %d %d g %d\n", chateau->y, chateau->x, 4-chateau->tpsProd);
            } else {
                fprintf(fichier, "B c %d %d m %d\n", chateau->y, chateau->x, 2-chateau->tpsProd);
            }
            perso = chateau->next;
            while (perso != NULL) {
                if (perso->nom == Seigneur) {
                    fprintf(fichier, "B s %d %d %d %d\n", perso->y, perso->x, perso->yDest, perso->xDest);
                } else if (perso->nom == Guerrier) {
                    fprintf(fichier, "B g %d %d %d %d\n", perso->y, perso->x, perso->yDest, perso->xDest);
                } else if (perso->nom == Manant) {
                    fprintf(fichier, "B m %d %d %d %d\n", perso->y, perso->x, perso->yDest, perso->xDest);
                }
                perso = perso->next;
            }
            chateau = chateau->vNext;
        }
        chateau = monde->chateauRouge;
        while (chateau != NULL) {
            if (chateau->tpsProd == 0) {
                fprintf(fichier, "R c %d %d\n", chateau->y, chateau->x);
            } else if (chateau->typeProd == Seigneur) {
                fprintf(fichier, "R c %d %d s %d\n", chateau->y, chateau->x, 6-chateau->tpsProd);
            } else if (chateau->typeProd == Guerrier) {
                fprintf(fichier, "R c %d %d g %d\n", chateau->y, chateau->x, 4-chateau->tpsProd);
            } else {
                fprintf(fichier, "R c %d %d m %d\n", chateau->y, chateau->x, 2-chateau->tpsProd);
            }
            perso = chateau->next;
            while (perso != NULL) {
                if (perso->nom == Seigneur) {
                    fprintf(fichier, "R s %d %d %d %d\n", perso->y, perso->x, perso->yDest, perso->xDest);
                } else if (perso->nom == Guerrier) {
                    fprintf(fichier, "R g %d %d %d %d\n", perso->y, perso->x, perso->yDest, perso->xDest);
                } else if (perso->nom == Manant) {
                    fprintf(fichier, "R m %d %d %d %d\n", perso->y, perso->x, perso->yDest, perso->xDest);
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
//Renvoie la longueur du fichier
int longueurFichier(FILE* fichier){
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

Monde* chargeFichier(FILE* fichier, int* tresorBleu, int* tresorRouge, int* debut){
    int len = longueurFichier(fichier);
    rewind(fichier);
     //Un tableau qui va contenir une ligne du fichier par case
    char** lignes = malloc((len)*sizeof(char*));
    for (int i = 0; i<len; i++) {
        lignes[i] = malloc(100*sizeof(char));
    }
    Personnage* mainBleu = NULL,* mainRouge = NULL;
    //Un tableau de pointeurs vers les personnages récupérés dans le fichier
    Personnage** personnages = malloc((len-3)*sizeof(Personnage*));
    for (int i = 0; i<len-3; i++) {
        personnages[i] = malloc(sizeof(Personnage));
    }
    //Lecture des 3 premières ligne contenant la dimension et les trésors
    fscanf(fichier, " %[^\n]s\n", lignes[0]);
    fscanf(fichier, " %[^\n]s\n", lignes[1]);
    fscanf(fichier, " %[^\n]s\n", lignes[2]);
    //Récupération de l'équipe en attente et des trésors
    if (lignes[1][0] == 'R') {
        *debut = 1;
        *tresorRouge = atoi(lignes[1]+2);
        *tresorBleu = atoi(lignes[2]+2);
    } else {
        *debut = 0;
        *tresorBleu = atoi(lignes[1]+2);
        *tresorRouge = atoi(lignes[2]+2);
    }
    // Lecture des lignes contenant les personnages
    for (int j = 3; j < len; j++) {
        fscanf(fichier, " %[^\n]s\n", lignes[j]);
    }
    for (int i = 3; i<len; i++) {
        int j = i - 3;
        // Si l'équipe est rouge
        if (charEstDans('R', lignes[i])) {
            personnages[j]->couleur = Rouge;
            // Si le personnage est un Chateau
            if (charEstDans('c', lignes[i])) {
                personnages[j]->nom = Chateau;
                personnages[j]->previous = NULL;
                personnages[j]->next = NULL;
                personnages[j]->vPrevious = mainRouge;
                personnages[j]->vNext = NULL;
                mainRouge = personnages[j];
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
                personnages[j]->num = incrementPerso(personnages[j]);
                personnages[j]->y = atoi(lignes[i]+4);
                personnages[j]->yDest = personnages[j]->y;
                personnages[j]->x = atoi(lignes[i]+6);
                personnages[j]->xDest = personnages[j]->x;
                personnages[j]->coupDeProd = 30;
            // Si le personnage n'est pas un chateau
            } else if (charEstDans('s', lignes[i])) {
                personnages[j]->nom = Seigneur;
                personnages[j]->y = atoi(lignes[i]+4);
                personnages[j]->x =  atoi(lignes[i]+6);
                personnages[j]->yDest = atoi(lignes[i]+8);
                personnages[j]->xDest = atoi(lignes[i]+10);
                personnages[j]->num = incrementPerso(personnages[j]);
                Personnage* persoInter = mainRouge;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
                personnages[j]->coupDeProd = 20;
            } else if (charEstDans('g', lignes[i])) {
                personnages[j]->nom = Guerrier;
                personnages[j]->y = atoi(lignes[i]+4);
                personnages[j]->x =  atoi(lignes[i]+6);
                personnages[j]->yDest = atoi(lignes[i]+8);
                personnages[j]->xDest = atoi(lignes[i]+10);
                personnages[j]->num = incrementPerso(personnages[j]);
                //mainRouge représente le dernier chateau Rouge retrouvé 
                //dans le fichier pour pouvoir le lier à ses agents
                Personnage* persoInter = mainRouge;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
                personnages[j]->coupDeProd = 5;
            } else {
                personnages[j]->nom = Manant;
                personnages[j]->y = atoi(lignes[i]+4);
                personnages[j]->x =  atoi(lignes[i]+6);
                personnages[j]->yDest = atoi(lignes[i]+8);
                char* a = lignes[i]+8;
                while (*a != 32) {
                    a++;
                }
                a++;
                personnages[j]->xDest = atoi(a);
                personnages[j]->num = incrementPerso(personnages[j]);
                Personnage* persoInter = mainRouge;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
                personnages[j]->coupDeProd = 1;
            }
        } else {
            //Si la couleur est Bleu
            personnages[j]->couleur = Bleu;
            if (charEstDans('c', lignes[i])) {
                personnages[j]->nom = Chateau;
                personnages[j]->previous = NULL;
                personnages[j]->next = NULL;
                personnages[j]->vPrevious = mainBleu;
                personnages[j]->vNext = NULL;
                mainBleu = personnages[j];
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
                personnages[j]->num = incrementPerso(personnages[j]);
                personnages[j]->y = atoi(lignes[i]+4);
                personnages[j]->yDest = personnages[j]->y;
                personnages[j]->x = atoi(lignes[i]+6);
                personnages[j]->xDest = personnages[j]->x;
                personnages[j]->coupDeProd = 30;
            } else if (charEstDans('s', lignes[i])) {
                personnages[j]->nom = Seigneur;
                personnages[j]->y = atoi(lignes[i]+4);
                personnages[j]->x =  atoi(lignes[i]+6);
                personnages[j]->yDest = atoi(lignes[i]+8);
                personnages[j]->xDest = atoi(lignes[i]+10);
                personnages[j]->num = incrementPerso(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
                personnages[j]->coupDeProd = 20;
            } else if (charEstDans('g', lignes[i])) {
                personnages[j]->nom = Guerrier;
                personnages[j]->y = atoi(lignes[i]+4);
                personnages[j]->x =  atoi(lignes[i]+6);
                personnages[j]->yDest = atoi(lignes[i]+8);
                personnages[j]->xDest = atoi(lignes[i]+10);
                personnages[j]->num = incrementPerso(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
                personnages[j]->coupDeProd = 5;
            } else {
                personnages[j]->nom = Manant;
                personnages[j]->y = atoi(lignes[i]+4);
                personnages[j]->x =  atoi(lignes[i]+6);
                personnages[j]->yDest = atoi(lignes[i]+8);
                char* a = lignes[i]+8;
                while (*a != 32) {
                    a++;
                }
                a++;
                personnages[j]->xDest = atoi(a);
                personnages[j]->num = incrementPerso(personnages[j]);
                Personnage* persoInter = mainBleu;
                while (persoInter->next){
                    persoInter = persoInter->next;
                }
                personnages[j]->previous = persoInter;
                persoInter->next = personnages[j];
                personnages[j]->next = NULL;
                personnages[j]->coupDeProd = 1;
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
    //Placer les personnages dans le monde
    for(int k = 0; k < len - 3 ; k++) {
        if (personnages[k]->nom == Chateau) {
            monde->plateau[personnages[k]->x][personnages[k]->y]->chateau = personnages[k];
        } else {
            if (monde->plateau[personnages[k]->x][personnages[k]->y]->perso == NULL) {
                monde->plateau[personnages[k]->x][personnages[k]->y]->perso = personnages[k];
            } else {
                Personnage* persoInterm = monde->plateau[personnages[k]->x][personnages[k]->y]->perso;
                while (persoInterm->vNext != NULL) {
                    persoInterm = persoInterm->vNext;
                }
                personnages[k]->vPrevious = persoInterm;
                persoInterm->vNext = personnages[k];
            }
        }
    }
    //Initialitation de chateauBleu et chateauRouge de la structure monde
    Personnage* chateauInter = mainRouge;
    while (chateauInter->vPrevious) {
        chateauInter = chateauInter->vPrevious;
    }
    monde->chateauRouge = chateauInter;
    chateauInter = mainBleu;
    while (chateauInter->vPrevious) {
        chateauInter = chateauInter->vPrevious;
    }
    monde->chateauBleu = chateauInter;
    return monde;
}
// renvoie 1 si un caractère donné apparait dans une chaine
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