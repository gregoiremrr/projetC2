#ifndef MONDE
#define MONDE

#include <stdio.h>

typedef enum
{
    Bleu,
    Rouge
} Couleur;

typedef enum
{
    Chateau,
    Seigneur,
    Guerrier,
    Manant,
    nul
} nomPerso;

typedef struct perso
{
    nomPerso nom;
    int x, y;
    int xDest, yDest;
    Couleur couleur;
    int tpsProd;
    nomPerso typeProd;
    struct perso *next, *previous;
    struct perso *vNext, *vPrevious;
} Personnage;

typedef struct
{
    Personnage *perso;
} Case;

typedef struct
{
    Case ***plateau;
    Personnage *chateauRouge, *chateauBleu;
} Monde;

Monde *initMonde(void);

void afficheMonde(Monde *monde, int tresorBleu, int tresorRouge, Couleur couleur);
void affichePersonage(Personnage *perso);
void afficheDeuxPersonage(Personnage *perso);
void initCounters();
int incrementAndGet(Couleur color, nomPerso perso);
#endif