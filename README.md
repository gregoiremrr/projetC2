# Project C2

### Compile: 

`gcc -Wall *.c -o main.out`

### Run:

`./main.out`

Running might not be possible due to permission issues, 

`chown your_username main.out`

1)Touches du clavier utiles au jeu:

-Pour l'action d'un chateau:
S : créer un Seigneur
G : créer un Guerrier
M : créer un Manant
R : Rien (cas où le trésor est insuffisant)

-Pour le seigneur
I : se transformer en château et devenir Immobile
D : se déplacer ( on choisit la colonne 1-8 puis la ligne 1-8)
s : suicide

-Pour le Guerrier
D : se déplacer ( on choisit la colonne 1-8 puis la ligne 1-8)
s : suicide

-Pour le manant
D : se déplacer ( on choisit la colonne 1-8 puis la ligne 1-8)
s : suicide

NB: un Seigneur ou un Guerrier ne peut pas rester immobile pendant un tour (sauf pour de transformer en château dans le cas du Seigneur)

2) Enregistrement/Chargement de la partie :
-L'utilisateur rentre seulement le nom du fichier à enregistrer ou à charger (sans l'extension got) c'est le programme qui se charge de la rajouter.
