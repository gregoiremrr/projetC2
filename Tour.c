#include <stdio.h>
#include<stdlib.h>

#include "monde.h"

void actionChateau(Personnage* chateau, int* tresor){
      char act;
      char perso;
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
        creerPersonnage(chateau, chateau->typeProd); // fonction à écrire
    
}

void actionSeigneur(Personnage* perso, int* tresor){
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
              }
          while (act == 'I' && *tresor < 30){
            printf("Donner une action pour le seigneur\n");
            scanf("%c", &act);
          }
          
          switch(act){
            case 's' : deletePerso(perso); // fonction delete à écrire
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
void actionGuerrier(Personnage* perso, int* tresor){
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
            case 's' : deletePerso(perso); // fonction delete à écrire
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

void actionManant(Personnage* perso, int* tresor){
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
            case 's' : deletePerso(perso); // fonction delete à écrire
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

