#include <stdio.h>
#include<stdlib.h>

#include "monde.h"
#include "creerPerso.h"

void actionChateau(Monde* monde, Personnage* chateau, int* tresor){
      char act;
      if (chateau->tpsProd == 0){
        do{
          printf("Donner l'action pour le chateau\n");
          scanf("%c", &act);
        } while ((act != 'S') && (act != 'G') && (act != 'M') && (act != 'R'));
          switch(act){
            case 'S' : chateau->tpsProd = 6;
                     tresor-= 20;
                     chateau->typeProd = Seigneur;
                     break;
            case 'G' : chateau->tpsProd = 4;
                     tresor-= 5;
                     chateau->typeProd = Guerrier;
                     
                     break;
            case 'M' : chateau->tpsProd = 2;
                     tresor-= 1;
                     chateau->typeProd = Manant;
                     break;
            case 'R' : break;
      }
    }
    else 
      chateau->tpsProd -= 1;
    if (chateau->tpsProd == 0 && chateau->typeProd != nul)
        creerPersonnage(monde, chateau, chateau->typeProd);
    
}

void actionSeigneur(Monde* monde, Personnage* perso, int* tresor){
        char act;
        int nDest1;
        int nDest2;
        if (perso->x == perso->xDest && perso->y == perso->yDest){
          do{
            printf("Donner une action pour le seigneur\n");
            scanf("%c", &act);
        } while ((act != 's') && (act != 'D') && (act != 'I') );
        }
        else{
          if (perso->x > nDest1)
             perso->x -= 1;
          else if (perso->x < nDest1)
              perso->x += 1;
          if (perso->y > nDest2)
              perso->y -= 1;
           else if (perso->y < nDest2)
              perso->y += 1;
          do{
            printf("Donner une action pour le seigneur\n");
            scanf("%c", &act);
          } while (act == 'I' && *tresor < 30);
          
          switch(act){
            case 's' : deletePerso(monde, perso);
                    break;
            case 'D' : do{
                        printf("Donner la nouvelle destination");
                        scanf("%d",&nDest1);
                        scanf("%d",&nDest2);
                      } while ((nDest1 == perso->x && nDest2 == perso->y) || (nDest1 < 0) || (nDest2 < 0));
                      if (perso->x > nDest1)
                          perso->x-=1;
                      else if (perso->x < nDest1)
                          perso->x+=1;
                      if (perso->y > nDest2)
                          perso->y-=1;
                      else if (perso->y < nDest2)
                          perso->y+=1;
                      break;
            // case 'I' : creerChateau(Personnage* chateau); pour la liste voisine
                      // break;
           }
  }
}

void actionGuerrier(Monde* monde, Personnage* perso, int* tresor){
        char act;
        int nDest1;
        int nDest2;
        if (perso->x == perso->xDest && perso->y == perso->yDest){
          do{
            printf("Donner une action pour le guerrier\n");
            scanf("%c", &act);
        } while ((act != 's') && (act != 'D'));
        }
        else{
          if (perso->x > nDest1)
             perso->x -= 1;
          else if (perso->x < nDest1)
              perso->x += 1;
          if (perso->y > nDest2)
              perso->y -= 1;
           else if (perso->y < nDest2)
              perso->y += 1;
              }
          
          switch(act){
            case 's' : deletePerso(monde, perso);
                    break;
            case 'D' : do{
                        printf("Donner la nouvelle destination");
                        scanf("%d",&nDest1);
                        scanf("%d",&nDest2);
                      } while ((nDest1 == perso->x && nDest2 == perso->y) || (nDest1 < 0) || (nDest2 < 0));
                      if (perso->x > nDest1)
                          perso->x-=1;
                      else if (perso->x < nDest1)
                          perso->x+=1;
                      if (perso->y > nDest2)
                          perso->y-=1;
                      else if (perso->y < nDest2)
                          perso->y+=1;
                      break;
          
           }
}

void actionManant(Monde* monde, Personnage* perso, int* tresor){
  char act;
        int nDest1;
        int nDest2;
        if (perso->x == perso->xDest && perso->y == perso->yDest){
          do{
            printf("Donner une action pour le manant\n");
            scanf("%c", &act);
        } while ((act != 's') && (act != 'D'));
        }
        else if (perso->x < 0 && perso->y < 0 ) 
            tresor += 1;
        
        else{
          if (perso->x > nDest1)
             perso->x -= 1;
          else if (perso->x < nDest1)
              perso->x += 1;
          if (perso->y > nDest2)
              perso->y -= 1;
           else if (perso->y < nDest2)
              perso->y += 1;
           }
        switch(act){
            case 's' : deletePerso(monde, perso);
                       break;
            case 'D' : do{
                        printf("Donner la nouvelle destination");
                        scanf("%d",&nDest1);
                        scanf("%d",&nDest2);
                      } while ((nDest1 == perso->x && nDest2 == perso->y) || (nDest1 < 0 && nDest2 > 0) || (nDest1 > 0 && nDest2 < 0));
                      if (nDest1 < 0 && nDest2 < 0)
                        tresor += 1;
                      else{
                        if (perso->x > nDest1)
                             perso->x -= 1;
                        else if (perso->x < nDest1)
                             perso->x += 1;
                        if (perso->y > nDest2)
                              perso->y -= 1;
                        else if (perso->y < nDest2)
                             perso->y += 1;
                        break;
                      }
}
}

void tour(Monde* monde, Couleur couleur, int* tresor){
  int k = 0;
  for (int i = 0; i<=7; i++){
    for (int j = 0; j<=7; j++){
      if(monde->plateau[i][j]->perso != NULL && monde->plateau[i][j]->perso->couleur == couleur){
        if(monde->plateau[i][j]->perso->nom == Chateau){
          actionChateau(monde, monde->plateau[i][j]->perso, tresor);
          k++;
        }
      }
    }
  }
  for (int i = 0; i<=7; i++){
    for (int j = 0; j<=7; j++){
      if(monde->plateau[i][j]->perso != NULL && monde->plateau[i][j]->perso->couleur == couleur){
        if(monde->plateau[i][j]->perso->nom == Manant){
          actionManant(monde, monde->plateau[i][j]->perso, tresor);
        }
        else if(monde->plateau[i][j]->perso->nom == Seigneur){
          actionSeigneur(monde, monde->plateau[i][j]->perso, tresor);
        }
        else if(monde->plateau[i][j]->perso->nom == Guerrier){
          actionGuerrier(monde, monde->plateau[i][j]->perso, tresor);
        }
        k++;
      }
    }
  }
}