#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "deplacement.h"
#include "monde.h"
#include "creerPerso.h"

void gereDeplacement(Monde* monde, Personnage* perso) {
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
            persoInter = persoInter->vNext;
        }
    }
    return p;
}