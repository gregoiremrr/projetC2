#ifndef MONDE
#define MONDE

#include <stdio.h>

 extern int partie;

typedef enum {Bleu, Rouge} Couleur;

typedef enum {Chateau, Seigneur, Guerrier, Manant, nul} nomPerso;

typedef struct perso {
    nomPerso nom;
    int x, y;
    int xDest, yDest;
    Couleur couleur;
    int tpsProd;
    nomPerso typeProd;
    int num;
    struct perso* next,* previous;
    struct perso* vNext,* vPrevious;
    int coupDeProd;
} Personnage;

typedef struct {
    Personnage* perso;
    Personnage* chateau;
} Case;

typedef struct {
    Case*** plateau;
    Personnage* chateauRouge,* chateauBleu;
} Monde;

void initPerso(Monde* monde, nomPerso nom, int x, int y, Couleur couleur, Personnage* chateau);

Monde* initMonde(void);

int incrementAndGet(Personnage* perso);

void afficheMonde(Monde* monde, int tresorBleu, int tresorRouge, Couleur couleur, int t);

#endif