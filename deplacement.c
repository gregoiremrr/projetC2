#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "deplacement.h"
#include "monde.h"
#include "creerPerso.h"

void gereDeplacement(Monde* monde, Personnage* perso) {
    //Chemin le plus court pour se déplacer vers une case
    int x = 0, y = 0;
    if (perso->x < perso->xDest) {
        x = 1;
    } else if (perso->x > perso->xDest) {
        x = -1;
    }
    if (perso->y < perso->yDest) {
        y = 1;
    } else if (perso->y > perso->yDest) {
        y = -1;
    }
    //Si aucun personnage n'est présent sur la case d'arrive
    if (monde->plateau[perso->x+x][perso->y+y]->perso == NULL && monde->plateau[perso->x+x][perso->y+y]->chateau == NULL) {
        monde->plateau[perso->x][perso->y]->perso = NULL;
        if (perso->vPrevious != NULL) {
            perso->vPrevious->vNext = perso->vNext;
            Personnage* persoInter = perso->vPrevious;
            while (persoInter->vPrevious != NULL) {
                persoInter = persoInter->vPrevious;
            }
            monde->plateau[perso->x][perso->y]->perso = persoInter;
            perso->vPrevious = NULL;
        }
        if (perso->vNext != NULL) {
            perso->vNext->vPrevious = perso->vPrevious;
            if (monde->plateau[perso->x][perso->y]->perso == NULL) {
                monde->plateau[perso->x][perso->y]->perso = perso->vNext;
            }
            perso->vNext = NULL;
        }
        perso->x += x;
        perso->y += y;
        monde->plateau[perso->x][perso->y]->perso = perso;
    //Si le personnage se déplace vers une case qui contient un chateau de même couleur
    } else if (monde->plateau[perso->x+x][perso->y+y]->perso == NULL && monde->plateau[perso->x+x][perso->y+y]->chateau->couleur == perso->couleur) {
        monde->plateau[perso->x][perso->y]->perso = NULL;
        if (perso->vPrevious != NULL) {
            perso->vPrevious->vNext = perso->vNext;
            Personnage* persoInter = perso->vPrevious;
            while (persoInter->vPrevious != NULL) {
                persoInter = persoInter->vPrevious;
            }
            monde->plateau[perso->x][perso->y]->perso = persoInter;
            perso->vPrevious = NULL;
        }
        if (perso->vNext != NULL) {
            perso->vNext->vPrevious = perso->vPrevious;
            if (monde->plateau[perso->x][perso->y]->perso == NULL) {
                monde->plateau[perso->x][perso->y]->perso = perso->vNext;
            }
            perso->vNext = NULL;
        }
        perso->x += x;
        perso->y += y;
        monde->plateau[perso->x][perso->y]->perso = perso;
    //Si le personnage se déplace vers une case qui contient un agent de même couleur
    } else if (monde->plateau[perso->x+x][perso->y+y]->perso != NULL && monde->plateau[perso->x+x][perso->y+y]->perso->couleur == perso->couleur) {
        monde->plateau[perso->x][perso->y]->perso = NULL;
        if (perso->vPrevious != NULL) {
            perso->vPrevious->vNext = perso->vNext;
            Personnage* persoInter = perso->vPrevious;
            while (persoInter->vPrevious != NULL) {
                persoInter = persoInter->vPrevious;
            }
            monde->plateau[perso->x][perso->y]->perso = persoInter;
            perso->vPrevious = NULL;
        }
        if (perso->vNext != NULL) {
            perso->vNext->vPrevious = perso->vPrevious;
            if (monde->plateau[perso->x][perso->y]->perso == NULL) {
                monde->plateau[perso->x][perso->y]->perso = perso->vNext;
            }
            perso->vNext = NULL;
        }
        perso->x += x;
        perso->y += y;
        if (perso->vNext != NULL) {
            perso->vNext->vPrevious = perso->vPrevious;
        }
        if (perso->vPrevious != NULL) {
            perso->vPrevious->vNext = perso->vNext;
        }
        Personnage* persoInter = monde->plateau[perso->x][perso->y]->perso;
        while (persoInter->vNext != NULL) {
            persoInter = persoInter->vNext;
        }
        persoInter->vNext = perso;
        perso->vPrevious = persoInter;
    //Si le personnage se déplace vers une case qui contient un chateau et un agent de même couleur
    } else if (monde->plateau[perso->x+x][perso->y+y]->perso != NULL 
            && monde->plateau[perso->x+x][perso->y+y]->chateau != NULL && monde->plateau[perso->x+x][perso->y+y]->perso->couleur == perso->couleur) {
        monde->plateau[perso->x][perso->y]->perso = NULL;
        if (perso->vPrevious != NULL) {
            perso->vPrevious->vNext = perso->vNext;
            Personnage* persoInter = perso->vPrevious;
            while (persoInter->vPrevious != NULL) {
                persoInter = persoInter->vPrevious;
            }
            monde->plateau[perso->x][perso->y]->perso = persoInter;
            perso->vPrevious = NULL;
        }
        if (perso->vNext != NULL) {
            perso->vNext->vPrevious = perso->vPrevious;
            if (monde->plateau[perso->x][perso->y]->perso == NULL) {
                monde->plateau[perso->x][perso->y]->perso = perso->vNext;
            }
            perso->vNext = NULL;
        }
        perso->x += x;
        perso->y += y;
        if (perso->vNext != NULL) {
            perso->vNext->vPrevious = perso->vPrevious;
        }
        if (perso->vPrevious != NULL) {
            perso->vPrevious->vNext = perso->vNext;
        }
        Personnage* persoInter = monde->plateau[perso->x][perso->y]->perso;
        while (persoInter->vNext != NULL) {
            persoInter = persoInter->vNext;
        }
        persoInter->vNext = perso;
        perso->vPrevious = persoInter;
    //Si le personnage se déplace vers une case qui contient un agent ou chateau de la couleur adverse
    } else {
        int p = 1;
        nomPerso persoNom = perso->nom;
        Couleur persoCouleur = perso->couleur;
        int persoNum = perso->num;
        if (monde->plateau[perso->x+x][perso->y+y]->perso != NULL) {
            p = engageCombatPerso(monde, perso, monde->plateau[perso->x+x][perso->y+y]->perso);
        }
        if (monde->plateau[perso->x+x][perso->y+y]->chateau != NULL && p==1) {
            p = engageCombatPerso(monde, perso, monde->plateau[perso->x+x][perso->y+y]->chateau);
        }
        if (p == 1) {
            if (persoNom == Seigneur) {
                if (persoCouleur == Bleu) {
                    printf("Le seigneur bleu %d est sorti vainqueur du combat !\n", persoNum);
                } else {
                    printf("Le seigneur rouge %d est sorti vainqueur du combat !\n", persoNum);
                }
            } else if (persoNom == Guerrier) {
                if (persoCouleur == Bleu) {
                    printf("Le guerrier bleu %d est sorti vainqueur du combat !\n", persoNum);
                } else {
                    printf("Le guerrier rouge %d est sorti vainqueur du combat !\n", persoNum);
                }
            } else {
                if (persoCouleur == Bleu) {
                    printf("Le manant bleu %d est sorti vainqueur du combat !\n", persoNum);
                } else {
                    printf("Le manant rouge %d est sorti vainqueur du combat !\n", persoNum);
                }
            }
            monde->plateau[perso->x][perso->y]->perso = NULL;
            if (perso->vPrevious != NULL) {
                perso->vPrevious->vNext = perso->vNext;
                Personnage* persoInter = perso->vPrevious;
                while (persoInter->vPrevious != NULL) {
                    persoInter = persoInter->vPrevious;
                }
                monde->plateau[perso->x][perso->y]->perso = persoInter;
                perso->vPrevious = NULL;
            }
            if (perso->vNext != NULL) {
                perso->vNext->vPrevious = perso->vPrevious;
                if (monde->plateau[perso->x][perso->y]->perso == NULL) {
                    monde->plateau[perso->x][perso->y]->perso = perso->vNext;
                }
                perso->vNext = NULL;
            }
            perso->x += x;
            perso->y += y;
            monde->plateau[perso->x][perso->y]->perso = perso;
        } else {
            if (persoNom == Seigneur) {
                if (persoCouleur == Bleu) {
                    printf("Le seigneur bleu %d est mort au combat !\n", persoNum);
                } else {
                    printf("Le seigneur rouge %d est mort au combat !\n", persoNum);
                }
            } else if (persoNom == Guerrier) {
                if (persoCouleur == Bleu) {
                    printf("Le guerrier bleu %d est mort au combat !\n", persoNum);
                } else {
                    printf("Le guerrier rouge %d est mort au combat !\n", persoNum);
                }
            } else {
                if (persoCouleur == Bleu) {
                    printf("Le manant bleu %d est mort au combat !\n", persoNum);
                } else {
                    printf("Le manant rouge %d est mort au combat !\n", persoNum);
                }
            }
        }
    }
}

int engageCombatPerso(Monde* monde, Personnage* persoAttaque, Personnage* persoDefend){
    srand(time(NULL));
    int p = 1; //variable nous permettant de vérifier si l'attaquant est en vie
    if (persoDefend->nom == Chateau) {//on gere le cas des chateau a part
        if (rand() % (persoAttaque->coupDeProd + persoDefend->coupDeProd) < persoAttaque->coupDeProd) {
            suppPerso(monde, persoDefend);
        } else {
            suppPerso(monde, persoAttaque);
            p = 0;
        }
    } else {
        Personnage* persoInter = persoDefend;
        Personnage* persoInterm;
        int verif = 1; //variable nous permettant de verifier s'il y a encore des defenseurs
        while (persoInter != NULL && p == 1) {
            verif = 1;
            if (persoInter->nom == Guerrier) {//les guerriers se battent en premier
                if (rand() % (persoAttaque->coupDeProd + persoInter->coupDeProd) < persoAttaque->coupDeProd) {
                    persoInterm = persoInter;
                    while (persoInterm->vPrevious != NULL) {
                        persoInterm = persoInterm->vPrevious;
                    }
                    persoDefend = persoInterm;
                    if (persoInter->vNext != NULL) {
                        persoInter = persoInter->vNext;
                        suppPerso(monde, persoInter->vPrevious);
                        verif = 0;
                    } else {
                        suppPerso(monde, persoInter);
                    }
                } else {
                    suppPerso(monde, persoAttaque);
                    p = 0;
                }
            }
            if (verif == 1) {
                persoInter = persoInter->vNext;
            }
        }
        persoInter = persoDefend;
        while (persoInter != NULL && p == 1) {
            verif = 1;
            if (persoInter->nom == Seigneur) {//les seigneurs se battent en second
                if (rand() % (persoAttaque->coupDeProd + persoInter->coupDeProd) < persoAttaque->coupDeProd) {
                    persoInterm = persoInter;
                    while (persoInterm->vPrevious != NULL) {
                        persoInterm = persoInterm->vPrevious;
                    }
                    persoDefend = persoInterm;
                    if (persoInter->vNext != NULL) {
                        persoInter = persoInter->vNext;
                        suppPerso(monde, persoInter->vPrevious);
                        verif = 0;
                    } else {
                        suppPerso(monde, persoInter);
                    }
                } else {
                    suppPerso(monde, persoAttaque);
                    p = 0;
                }
            }
            if (verif == 1) {
                persoInter = persoInter->vNext;
            }
        }
        persoInter = persoDefend;
        while (persoInter != NULL && p == 1) {
            verif = 1;
            if (persoInter->nom == Manant) {//les manants se battent en dernier
                if (rand() % (persoAttaque->coupDeProd + persoInter->coupDeProd) < persoAttaque->coupDeProd) {
                    persoInterm = persoInter;
                    while (persoInterm->vPrevious != NULL) {
                        persoInterm = persoInterm->vPrevious;
                    }
                    persoDefend = persoInterm;
                    if (persoInter->vNext != NULL) {
                        persoInter = persoInter->vNext;
                        suppPerso(monde, persoInter->vPrevious);
                        verif = 0;
                    } else {
                        suppPerso(monde, persoInter);
                    }
                } else {
                    suppPerso(monde, persoAttaque);
                    p = 0;
                }
            }
            if (verif == 1) {
                persoInter = persoInter->vNext;
            }
        }
    }
    return p;
}

//Vérifie l'homogéinité des couleurs sur le plateau
void verifCombat(Monde* monde, Personnage* manant){
    int x = manant->x, y = manant->y;
    int len = 0;
    Personnage* persoInter = monde->plateau[x][y]->perso;
    while (persoInter != NULL) {
        persoInter = persoInter->vNext;
        len++;
    }
    Personnage** tableauBleu = malloc(len*sizeof(Personnage*));
    Personnage** tableauRouge = malloc(len*sizeof(Personnage*));
    for (int i = 0; i<len; i++) {
        tableauBleu[i] = NULL;
        tableauRouge[i] = NULL;
    }
    persoInter = monde->plateau[x][y]->perso;
    int i = 0, j = 0;
    while (persoInter != NULL) {//on classe les personnages de la case dans deux tableaux selon leur couleur
        if (persoInter->couleur == Bleu) {
            tableauBleu[i] = persoInter;
            i++;
        } else {
            tableauRouge[j] = persoInter;
            j++;
        }
        persoInter = persoInter->vNext;
    }
    if (monde->plateau[x][y]->chateau != NULL) {//on met le chateau le dernier puisque c'est le dernier a se battre
        if (monde->plateau[x][y]->chateau->couleur == Bleu) {
            tableauBleu[i] = monde->plateau[x][y]->chateau;
        } else {
            tableauRouge[j] = monde->plateau[x][y]->chateau;
        }
    }
    int vieManant;
    Personnage**  tabAtt,** tabDef;
    if (manant->couleur == Bleu) {
        tabAtt = tableauBleu;
        tabDef = tableauRouge;
    } else {
        tabAtt = tableauRouge;
        tabDef = tableauBleu;
    }
    if (tabDef[0] != NULL) {//on provoque les combats
        i = 1;
        j = 1;
        Personnage* persoAttaque = tabAtt[0];
        Personnage* persoDefend = tabDef[0];
        while (persoAttaque != NULL && persoDefend != NULL) {
            vieManant = 1;
            while (persoDefend != NULL && vieManant == 1) {
                if (rand() % (persoAttaque->coupDeProd + persoDefend->coupDeProd) < persoAttaque->coupDeProd) {
                    if (persoAttaque->couleur == Bleu) {
                        printf("Le manant bleu %d est sorti vainqueur du combat !\n", persoAttaque->num);
                    } else {
                        printf("Le manant rouge %d est sorti vainqueur du combat !\n", persoAttaque->num);
                    }
                    if (persoDefend->vNext != NULL) {
                        persoDefend = persoDefend->vNext;
                        suppPerso(monde, persoDefend->vPrevious);
                    } else {
                        suppPerso(monde, persoDefend);
                    }
                    persoDefend = tabDef[j];
                    j++;
                } else {
                    if (persoAttaque->couleur == Bleu) {
                        printf("Le manant bleu %d est mort au combat...\n", persoAttaque->num);
                    } else {
                        printf("Le manant rouge %d est mort au combat...\n", persoAttaque->num);
                    }
                    suppPerso(monde, persoAttaque);
                    vieManant = 0;
                }
            }
            persoAttaque = tabAtt[i];
            i++;
        }
    }
    free(tableauRouge);
    free(tableauBleu);
}