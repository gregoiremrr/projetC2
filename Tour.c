#include <stdio.h>
#include <stdlib.h>

#include "monde.h"
#include "creerPerso.h"

void actionChateau(Monde *monde, Personnage *chateau, int *tresor)
{
  char act = 'a';
  if (chateau->tpsProd == 0)
  {
    while ((act != 'S') && (act != 'G') && (act != 'M') && (act != 'R'))
    {
      printf("Donner l'action pour le chateau :\n");
      scanf(" %c", &act);
    }
    if (act != 'a')
    {
      switch (act)
      {
      case 'S':
        chateau->tpsProd = 6;
        *tresor -= 20;
        chateau->typeProd = Seigneur;
        break;
      case 'G':
        chateau->tpsProd = 4;
        *tresor -= 5;
        chateau->typeProd = Guerrier;

        break;
      case 'M':
        chateau->tpsProd = 2;
        *tresor -= 1;
        chateau->typeProd = Manant;
        break;
      case 'R':
        break;
      }
    }
  }
  else
  {
    if (chateau->tpsProd > 1)
    {
      printf("Un personnage est en cours de construction, le tour du château est sauté\n");
    }
    chateau->tpsProd -= 1;
    if (chateau->tpsProd == 0)
    {
      creerPersonnage(monde, chateau, chateau->typeProd);
      actionChateau(monde, chateau, tresor);
    }
  }
}

void actionSeigneur(Monde *monde, Personnage *perso, int *tresor)
{
  char act = 'n';
  if (perso->x == perso->xDest && perso->y == perso->yDest)
  {
    printf("Donner une action pour le seigneur :\n");
    scanf(" %c", &act);
    while ((act != 's') && (act != 'D') && (act != 'I'))
    {
      printf("Action invalide. Donner une autre action pour le seigneur\n");
      scanf(" %c", &act);
    }
  }
  else
  {
    printf("Le personnage %u est en déplacement\n", perso->nom);
    monde->plateau[perso->x][perso->y]->perso = NULL;
    if (perso->x > perso->xDest)
      perso->x -= 1;
    else if (perso->x < perso->xDest)
      perso->x += 1;
    if (perso->y > perso->yDest)
      perso->y -= 1;
    else if (perso->y < perso->yDest)
      perso->y += 1;
    monde->plateau[perso->x][perso->y]->perso = perso;
  }

  while (*tresor < 30 && act == 'I')
  {
    printf("Tresor insuffisant. Donner une action pour le seigneur\n");
    scanf(" %c", &act);
  }
  if (act != 'n')
  {
    switch (act)
    {
    case 's':
      deletePerso(monde, perso);
      break;
    case 'D':
      do
      {
        printf("Donner la nouvelle destination :\n");
        scanf("%d", &perso->yDest);
        perso->yDest -= 1;
        scanf("%d", &perso->xDest);
        perso->xDest -= 1;
      } while ((perso->xDest == perso->x && perso->yDest == perso->y) || (perso->xDest < 0) ||
               (perso->yDest < 0) || perso->xDest > 7 || perso->yDest > 7);
      monde->plateau[perso->x][perso->y]->perso = NULL;
      if (perso->x > perso->xDest)
        perso->x -= 1;
      else if (perso->x < perso->xDest)
        perso->x += 1;
      if (perso->y > perso->yDest)
        perso->y -= 1;
      else if (perso->y < perso->yDest)
        perso->y += 1;
      monde->plateau[perso->x][perso->y]->perso = perso;
      break;
    case 'I':
      creerChateau(monde, perso);
      *tresor -= 30;
    }
  }
}

void actionGuerrier(Monde *monde, Personnage *perso, int *tresor)
{
  char act = 'n';
  if (perso->x == perso->xDest && perso->y == perso->yDest)
  {
    do
    {
      printf("Donner une action pour le guerrier :\n");
      scanf(" %c", &act);
    } while ((act != 's') && (act != 'D'));
  }
  else
  {
    printf("Le personnage %u est en déplacement \n", perso->nom);
    monde->plateau[perso->x][perso->y]->perso = NULL;
    if (perso->x > perso->xDest)
      perso->x -= 1;
    else if (perso->x < perso->xDest)
      perso->x += 1;
    if (perso->y > perso->yDest)
      perso->y -= 1;
    else if (perso->y < perso->yDest)
      perso->y += 1;
    monde->plateau[perso->x][perso->y]->perso = perso;
  }
  if (act != 'n')
  {
    switch (act)
    {
    case 's':
      deletePerso(monde, perso);
      break;
    case 'D':
      do
      {
        printf("Donner la nouvelle destination :\n");
        scanf("%d", &perso->yDest);
        perso->yDest -= 1;
        scanf("%d", &perso->xDest);
        perso->xDest -= 1;
      } while ((perso->xDest == perso->x && perso->yDest == perso->y) || (perso->xDest < 0) ||
               (perso->yDest < 0) || perso->xDest > 7 || perso->yDest > 7);
      monde->plateau[perso->x][perso->y]->perso = NULL;
      if (perso->x > perso->xDest)
        perso->x -= 1;
      else if (perso->x < perso->xDest)
        perso->x += 1;
      if (perso->y > perso->yDest)
        perso->y -= 1;
      else if (perso->y < perso->yDest)
        perso->y += 1;
      monde->plateau[perso->x][perso->y]->perso = perso;
      break;
    }
  }
}

void actionManant(Monde *monde, Personnage *perso, int *tresor)
{
  if (perso->xDest >= 0 && perso->yDest >= 0)
  {
    char act = 'n';
    if (perso->x == perso->xDest && perso->y == perso->yDest)
    {
      do
      {
        printf("Donner une action pour le manant :\n");
        scanf(" %c", &act);
      } while ((act != 's') && (act != 'D'));
    }
    else if (perso->x < 0 && perso->y < 0)
      *tresor += 1;

    else
    {
      printf("Le personnage %u est en déplacement\n", perso->nom);
      monde->plateau[perso->x][perso->y]->perso = NULL;
      if (perso->x > perso->xDest)
        perso->x -= 1;
      else if (perso->x < perso->xDest)
        perso->x += 1;
      if (perso->y > perso->yDest)
        perso->y -= 1;
      else if (perso->y < perso->yDest)
        perso->y += 1;
      monde->plateau[perso->x][perso->y]->perso = perso;
    }
    if (act != 'n')
    {
      switch (act)
      {
      case 's':
        deletePerso(monde, perso);
        break;
      case 'D':
        do
        {
          printf("Donner la nouvelle destination :\n");
          scanf("%d", &perso->yDest);
          perso->yDest -= 1;
          scanf("%d", &perso->xDest);
          perso->xDest -= 1;
        } while ((perso->xDest == perso->x && perso->yDest == perso->y) || (perso->xDest < 0 && perso->yDest > 0) || (perso->xDest > 0 && perso->yDest < 0) || perso->xDest > 7 || perso->yDest > 7);
        if (perso->xDest < 0 && perso->yDest < 0)
          *tresor += 1;
        else
        {
          monde->plateau[perso->x][perso->y]->perso = NULL;
          if (perso->x > perso->xDest)
            perso->x -= 1;
          else if (perso->x < perso->xDest)
            perso->x += 1;
          if (perso->y > perso->yDest)
            perso->y -= 1;
          else if (perso->y < perso->yDest)
            perso->y += 1;
          monde->plateau[perso->x][perso->y]->perso = perso;
          break;
        }
      }
    }
  }
}

void tour(Monde *monde, Couleur couleur, int *tresor, int *tresor2)
{
  Personnage *chateau;
  if (couleur == Bleu)
  {
    chateau = monde->chateauBleu;
  }
  else
  {
    chateau = monde->chateauRouge;
  }
  while (chateau->vNext != NULL)
  {
    actionChateau(monde, chateau, tresor);
    afficheMonde(monde, *tresor, *tresor2, couleur);
    printf("\n");
    chateau = chateau->vNext;
  }
  actionChateau(monde, chateau, tresor);
  afficheMonde(monde, *tresor, *tresor2, couleur);
  printf("\n");

  while (chateau)
  {
    Personnage *perso = chateau->next;
    while (perso)
    {
      if (perso->nom == Seigneur)
      {
        actionSeigneur(monde, perso, tresor);
        afficheMonde(monde, *tresor, *tresor2, couleur);
        printf("\n");
      }
      else if (perso->nom == Guerrier)
      {
        actionGuerrier(monde, perso, tresor);
        afficheMonde(monde, *tresor, *tresor2, couleur);
        printf("\n");
      }
      else
      {
        actionManant(monde, perso, tresor);
        afficheMonde(monde, *tresor, *tresor2, couleur);
        printf("\n");
      }
      perso = perso->next;
    }
    chateau = chateau->vPrevious;
  }
}