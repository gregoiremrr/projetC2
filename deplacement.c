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
    //Si aucun personnage n'est présent sur la case
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
        //Si le personnage était sur une case avec d'autres personnages
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
    } else if (monde->plateau[perso->x+x][perso->y+y]->perso != NULL && monde->plateau[perso->x+x][perso->y+y]->chateau != NULL && monde->plateau[perso->x+x][perso->y+y]->perso->couleur == perso->couleur) {
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
    //Si le personnage se déplace vers une case qui contient un agent ou chateau pas de la même couleur
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
    int p = 1;
    if (persoDefend->nom == Chateau) {
        if (rand() % (persoAttaque->coupDeProd + persoDefend->coupDeProd) < persoAttaque->coupDeProd) {
            deletePerso(monde, persoDefend);
        } else {
            deletePerso(monde, persoAttaque);
            p = 0;
        }
    } else {
        Personnage* persoInter = persoDefend;
        while (persoInter != NULL && p == 1) {
            if (persoInter->couleur != persoAttaque->couleur) {
                if (persoInter->nom == Guerrier) {
                    if (rand() % (persoAttaque->coupDeProd + persoInter->coupDeProd) < persoAttaque->coupDeProd) {
                        if (persoInter->vNext != NULL) {
                            persoInter = persoInter->vNext;
                            deletePerso(monde, persoInter->vPrevious);
                        } else {
                            deletePerso(monde, persoInter);
                        }
                    } else {
                        deletePerso(monde, persoAttaque);
                        p = 0;
                    }
                } else if (persoInter->nom == Seigneur) {
                    if (rand() % (persoAttaque->coupDeProd + persoInter->coupDeProd) < persoAttaque->coupDeProd) {
                        if (persoInter->vNext != NULL) {
                            persoInter = persoInter->vNext;
                            deletePerso(monde, persoInter->vPrevious);
                        } else {
                            deletePerso(monde, persoInter);
                        }
                    } else {
                        deletePerso(monde, persoAttaque);
                        p = 0;
                    }
                } else {
                    if (rand() % (persoAttaque->coupDeProd + persoInter->coupDeProd) < persoAttaque->coupDeProd) {
                        if (persoInter->vNext != NULL) {
                            persoInter = persoInter->vNext;
                            deletePerso(monde, persoInter->vPrevious);
                        } else {
                            deletePerso(monde, persoInter);
                        }
                    } else {
                        deletePerso(monde, persoAttaque);
                        p = 0;
                    }
                }
            } else {
                Personnage* persoInterm = persoAttaque;
                while (persoInterm->vNext != NULL) {
                    persoInterm = persoInterm->vNext;
                }
                persoInterm->vNext = persoInter;
                persoInter->vPrevious = persoInterm;
                persoInter->vNext = NULL;
            }
            persoInter = persoInter->vNext;
        }
    }
    return p;
}

//Vérifie l'homogéinité des couleurs sur le plateau
void verifCombat(Monde* monde, Personnage* manant){
    int k;
    Personnage* persoInterm;
    if (manant->couleur == Bleu) {
        persoInterm = monde->chateauBleu;
    } else {
        persoInterm = monde->chateauRouge;
    }
    while (persoInterm != NULL) {printf("ok2\n");
        if (persoInterm->nom == Manant) {
            k = 1;
            Personnage* vInter = monde->plateau[persoInterm->x][persoInterm->y]->perso;
            while (vInter != NULL) {printf("ok3\n");
                if (vInter->couleur != manant->couleur) {printf("ok4\n");
                    k = engageCombatPerso(monde, persoInterm, vInter);
                    if (k==1) {printf("ok5\n");
                        if (persoInterm->nom == Seigneur) {
                            if (persoInterm->couleur == Bleu) {
                                printf("Le seigneur bleu %d est sorti vainqueur du combat !\n", manant->num);
                            } else {printf("ok6\n");
                                printf("Le seigneur rouge %d est sorti vainqueur du combat !\n", manant->num);
                            }
                        } else if (persoInterm->nom == Guerrier) {printf("ok8\n");
                            if (persoInterm->couleur == Bleu) {
                                printf("Le guerrier bleu %d est sorti vainqueur du combat !\n", manant->num);
                            } else {
                                printf("Le guerrier rouge %d est sorti vainqueur du combat !\n", manant->num);
                            }
                        } else {printf("ok9\n");
                            if (persoInterm->couleur == Bleu) {
                                printf("Le manant bleu %d est sorti vainqueur du combat !\n", manant->num);
                            } else {printf("ok10\n");
                                printf("Le manant rouge %d est sorti vainqueur du combat !\n", manant->num);
                            }
                        }
                    }
                    break;
                }
                vInter = vInter->vNext;printf("ok11\n");
            }
            if (monde->plateau[persoInterm->x][persoInterm->y]->chateau != NULL && k == 1) {
                k = engageCombatPerso(monde, persoInterm, monde->plateau[persoInterm->x][persoInterm->y]->chateau);
            }
        }
        persoInterm = persoInterm->next;
    }
}
