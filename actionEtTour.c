#include <stdio.h>
#include <stdlib.h>

#define RED '\033[31m'
#define BLUE '\033[34m'

#include "actionEtTour.h"
#include "monde.h"
#include "creerPerso.h"
#include "deplacement.h"

//verifie si le chateau est deja en train de jouer et sinon lui demande une action
void actionChateau(Monde* monde, Personnage* chateau, int* tresor, int* tresor2) {
    if (chateau->tpsProd > 0) {
        if (chateau->tpsProd > 1) {
            if (chateau->couleur == Bleu) {
                if (chateau->typeProd == Seigneur) {
                    printf("Un seigneur est en cours de construction dans le chateau bleu %d (plus que %d tour(s))\n", chateau->num, chateau->tpsProd-1);
                } else if (chateau->typeProd == Guerrier) {
                    printf("Un guerrier est en cours de construction dans le chateau bleu %d (plus que %d tour(s))\n", chateau->num, chateau->tpsProd-1);
                } else {
                    printf("Un manant est en cours de construction dans le chateau bleu %d (plus que %d tour(s))\n", chateau->num, chateau->tpsProd-1);
                }
            } else {
                if (chateau->typeProd == Seigneur) {
                    printf("Un seigneur est en cours de construction dans le chateau rouge %d (plus que %d tour(s))\n", chateau->num, chateau->tpsProd-1);
                } else if (chateau->typeProd == Guerrier) {
                    printf("Un guerrier est en cours de construction dans le chateau rouge %d (plus que %d tour(s))\n", chateau->num, chateau->tpsProd-1);
                } else {
                    printf("Un manant est en cours de construction dans le chateau rouge %d (plus que %d tour(s))\n", chateau->num, chateau->tpsProd-1);
                }
            }            
        }
        chateau->tpsProd -= 1;
        if (chateau->tpsProd == 0) {
            creerPersonnage(monde, chateau, chateau->typeProd);
            chateau->typeProd = nul;
            if (chateau->couleur == Bleu) {
                printf("Le chateau bleu %d a produit un agent !\n", chateau->num);
            } else {
                printf("Le chateau rouge %d a produit un agent !\n", chateau->num);
            }
            if (chateau->couleur == Bleu){
                printf("\033[34mTresor bleu  : %d\n\033[31mTresor rouge : %d\n\033[37m\033[49m", *tresor, *tresor2);
            } else {
                printf("\033[34mTresor bleu  : %d\n\033[31mTresor rouge : %d\n\033[37m\033[49m", *tresor2, *tresor);
            }
            afficheMonde(monde, chateau->couleur, *tresor, *tresor2, 0);
        }
    }
    if (chateau->tpsProd == 0 && chateau->typeProd == nul) {
        char act = 'a';
        while ((act != 'S' || *tresor < 20) && (act != 'G' || *tresor < 5) && (act != 'M' || *tresor < 1) &&  act != 'R') {
            if (chateau->couleur == Bleu) {
                printf("Entrez une action pour le chateau bleu %d :(S/M/G/R)\n", chateau->num);
            } else {
                printf("Entrez une action pour le chateau rouge %d :(S/M/G/R)\n", chateau->num);
            }
            scanf(" %c", &act);
            if ((act == 'S' && *tresor < 20)||(act == 'G' && *tresor < 5)||(act == 'M' && *tresor < 1)){
                printf("Tresor bleu insuffisant... (%d piece(s))\n", *tresor);
            }
        }
        switch(act) {
            case 'S' :
                chateau->tpsProd = 6;
                *tresor -= 20;
                chateau->typeProd = Seigneur;
                break;
            case 'G' :
                chateau->tpsProd = 4;
                *tresor -= 5;
                chateau->typeProd = Guerrier;
                break;
            case 'M' :
                chateau->tpsProd = 2;
                *tresor -= 1;
                chateau->typeProd = Manant;
        }
    }
}

//verifie si le seigneur est deja en train de jouer et sinon lui demande une action
void actionSeigneur(Monde* monde, Personnage* perso, int* tresor) {
    if (perso->x == perso->xDest && perso->y == perso->yDest) {
        char act = 'a';
        while (act != 's' && act != 'D' && (act != 'I' || *tresor < 30 || monde->plateau[perso->x][perso->y]->chateau != NULL)) {
            if (perso->couleur == Bleu) {
                printf("Entrez une action pour le seigneur bleu %d :(I/D/s)\n", perso->num);
            } else {
                printf("Entrez une action pour le seigneur rouge %d :(I/D/s)\n", perso->num);
            }
            scanf(" %c", &act);
            if (act == 'I' && *tresor < 30) {
                if (perso->couleur == Bleu) {
                    printf("Tresor bleu insuffisant... (%d piece(s))\n", *tresor);
                } else {
                    printf("Tresor rouge insuffisant... (%d piece(s))\n", *tresor);
                }
                
            } else if (act == 'I' && monde->plateau[perso->x][perso->y]->chateau != NULL) {
                printf("Un chateau est deja present sur cette case...\n");
            }
        }
        switch(act) {
            case 's' :
                suppPerso(monde, perso);
                break;
            case 'D' :
                do{
                    if (perso->couleur == Bleu) {
                        printf("Entrez une destination pour le seigneur bleu %d :(col:1-8 ,ligne: 1-8)\n", perso->num);
                    } else {
                        printf("Entrez une destination pour le seigneur rouge %d :(col:1-8 ,ligne: 1-8)\n", perso->num);
                    }
                    scanf("%d",&perso->yDest);
                    perso->yDest -= 1;
                    scanf("%d",&perso->xDest);
                    perso->xDest -= 1;
                } while ((perso->xDest == perso->x && perso->yDest == perso->y) || (perso->xDest < 0) || (perso->yDest < 0) || perso->xDest > 7 || perso->yDest > 7 );
                gereDeplacement(monde, perso);
                break;
            case 'I' :
                creerChateau(monde, perso);
                *tresor -= 30;
        }
    } else {
        if (perso->couleur == Bleu) {
            printf("Le seigneur bleu %d est en deplacement pendant ce tour...\n", perso->num);
        } else {
            printf("Le seigneur rouge %d est en deplacement pendant ce tour...\n", perso->num);
        }
        gereDeplacement(monde, perso);
    }
}

//verifie si le guerrier est deja en train de jouer et sinon lui demande une action
void actionGuerrier(Monde* monde, Personnage* perso) {
    if (perso->x == perso->xDest && perso->y == perso->yDest) {
        char act = 'a';
        while (act != 's' && act != 'D') {
            if (perso->couleur == Bleu) {
                printf("Entrez une action pour le guerrier bleu %d :(D/s)\n", perso->num);
            } else {
                printf("Entrez une action pour le guerrier rouge %d :(D/s)\n", perso->num);
            }
            scanf(" %c", &act);
        }
        switch(act) {
            case 's' :
                suppPerso(monde, perso);
                break;
            case 'D' :
                do{
                    if (perso->couleur == Bleu) {
                        printf("Entrez une destination pour le guerrier bleu %d :(col:1-8 ,ligne: 1-8)\n", perso->num);
                    } else {
                        printf("Entrez une destination pour le guerrier rouge %d :(col:1-8 ,ligne: 1-8)\n", perso->num);
                    }
                    scanf("%d",&perso->yDest);
                    perso->yDest -= 1;
                    scanf("%d",&perso->xDest);
                    perso->xDest -= 1;
                } while ((perso->xDest == perso->x && perso->yDest == perso->y) || (perso->xDest < 0) || (perso->yDest < 0) || perso->xDest > 7 || perso->yDest > 7 );
                gereDeplacement(monde, perso);
        }
    } else {
        if (perso->couleur == Bleu) {
            printf("Le guerrier bleu %d est en deplacement pendant ce tour...\n", perso->num);
        } else {
            printf("Le guerrier rouge %d est en deplacement pendant ce tour...\n", perso->num);
        }
        gereDeplacement(monde, perso);
    }
}

//verifie si le manant est deja en train de jouer et sinon lui demande une action
void actionManant(Monde* monde, Personnage* perso, int* tresor) {
    if (perso->x == perso->xDest && perso->y == perso->yDest) {
        char act = 'a';
        while (act != 's' && act != 'D') {
            if (perso->couleur == Bleu) {
                printf("Entrez une action pour le manant bleu %d :(D/s)\n", perso->num);
            } else {
                printf("Entrez une action pour le manant rouge %d :(D/s)\n", perso->num);
            }
            scanf(" %c", &act);
        }
        switch (act){
            case 's' :
                suppPerso(monde, perso);
                break;
            case 'D' :
                do{
                    if (perso->couleur == Bleu) {
                        printf("Entrez une destination pour le manant bleu %d :(col:1-8 ,ligne: 1-8)\n", perso->num);
                    } else {
                        printf("Entrez une destination pour le manant rouge %d :(col:1-8 ,ligne: 1-8)\n", perso->num);
                    }
                    scanf("%d",&perso->yDest);
                    perso->yDest -= 1;
                    scanf("%d",&perso->xDest);
                    perso->xDest -= 1;
                } while ((perso->xDest == perso->x && perso->yDest == perso->y) ||  (perso->xDest < 0 && perso->yDest > 0) || (perso->xDest > 0 && perso->yDest < 0) || perso->xDest > 7 || perso->yDest > 7);
                if (perso->xDest >= 0 && perso->yDest >= 0) {
                    gereDeplacement(monde, perso);
                }
        }
    } else if (perso->xDest >= 0 && perso->yDest >= 0) {
        if (perso->couleur == Bleu) {
            printf("Le manant bleu %d est en deplacement pendant ce tour...\n", perso->num);
        } else {
            printf("Le manant rouge %d est en deplacement pendant ce tour...\n", perso->num);
        }
        gereDeplacement(monde, perso);
    } else {
        if (perso->couleur == Bleu) {
            printf("Le manant bleu %d ajoute une pièce au tresor !\n", perso->num);
        } else {
            printf("Le manant rouge %d ajoute une pièce au tresor !\n", perso->num);
        }
        *tresor += 1;
    }
}

//gere le tour de chaque couleur en demandant d'abord au chateau puis aux agents
//tresor est le tresor de l'equipe en train de jouer
//tresor2 est le tresor de l'equipe adverse
void tour(Monde* monde, Couleur couleur, int* tresor, int* tresor2){
    Personnage* chateau;
    if (couleur == Bleu) {
        chateau = monde->chateauBleu;
    } else {
        chateau = monde->chateauRouge;
    }
    while (chateau->vNext != NULL) {
        actionChateau(monde, chateau, tresor, tresor2);
        afficheMonde(monde, *tresor, *tresor2, couleur, 1);
        printf("\n");
        chateau = chateau->vNext;
    }
    actionChateau(monde, chateau, tresor, tresor2);
    afficheMonde(monde, *tresor, *tresor2, couleur, 1);
    printf("\n");

    while (chateau != NULL) {
        Personnage* perso = chateau->next;
        while (perso != NULL && partie == 1) {
            if (perso->nom == Seigneur) {
                actionSeigneur(monde, perso, tresor);
                afficheMonde(monde, *tresor, *tresor2, couleur, 1);
                printf("\n");
            } else if (perso->nom == Guerrier) {
                actionGuerrier(monde, perso);
                afficheMonde(monde, *tresor, *tresor2, couleur, 1);
                printf("\n");
            } else {
                actionManant(monde, perso, tresor);
                afficheMonde(monde, *tresor, *tresor2, couleur, 1);
                printf("\n");
            }
            perso = perso->next;
        }
        chateau = chateau->vPrevious;
    }
}