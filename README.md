# puzzle-game
Had to code the Fifteen puzzle game and make it doable in different dimensions 

# Projet de Programmation : Le Taquin

**Dodeman Léna**

**Leger Bertrand**

## Phase de réflexion

On a chacun de notre coté joué au jeu en ligne pour comprendre le fonctionnement de
déplacement de case et de résolution. On a ensuite discuté des fonctions nécessaires à
la réalisation du code pour le jeu. Plusieurs fonctions nous viennent en tête au début
de notre réflexion :

* Fonction qui vérifie que le tableau soit soluble
* Fonction qui prend les touches gauche droite haut bas
* Fonction qui déplace la case vide
* Fonction qui vérifie si le tableau est résolu
* Fonction qui mélange le tableau id
* Fonction qui prend un tableau depuis un fichier
* Fonction qui créer le tableau Tid nxn (avec malloc)
* Un printf et scanf qui demande la taille n du jeu voulu nxn
* Fonction qui renvoie la position de la case vide
* Fonction qui effectue un nombre aléatoire de déplacement et a chaque
déplacement il a 4 choix qu'il doit effectuer en aléatoire
* Fonction qui utilise la veriftab et affichetab a chaque fois qu'une touche et
appuyée et qu'une case est déplacée
* La fonction qui vérifiera si le tableau est solvable sera utilisée pour les
grilles obtenues dans un fichier car pour les autres tableaux, on partira d’un
tableau résolu pour faire des déplacements aléatoires donc il sera forcément
solvable
* On a établi que la case vide serait le zéro

Nous avons ensuite pris connaissance du fait que tous les mélanges aléatoires ne
peuvent pas forcément être résolu. Il faut un nombre paire de déplacement de la case
vide de sa position initiale à la position finale, et ce nombre paire doit être égal
au nombre pair d’échange successifs de deux cases pour que l’ensemble soit trié.

Lors de la programmation, des fonctions écrites plus haut sont réunies en une seule.

## Fonction de déplacement

Le but de cette fonction est de pouvoir se déplacer dans la grille selon les
contraintes des règles du Taquin. Dans ce jeu on ne peut que se déplacer vers la case
vide afin de résoudre le puzzle. Nous avons donc analysé les différents déplacements
afin de savoir quelles cases il fallait échanger dans notre tableau, et comment
l'écrire en code C. Le principe est que si nous nous déplaçons vers le haut, la case
vide va vers le bas, l'inversement est le même pour tous les déplacements.

* Déplacement vers le haut : On échange la case vide avec la case en dessous de celle-
ci. Si la case vide est tab[x][y] alors on l'échange avec tab[x][y+1].

* Déplacement vers le bas : On échange la case vide avec la case au dessus de celle-ci.
Si la case vide est tab[x][y] alors on l'échange avec tab[x][y-1].


* Déplacement vers la droite : On échange la case vide avec la case à gauche de celle-
ci. Si la case vide est tab[x][y] alors on l'échange avec tab[x-1][y].

* Déplacement vers la gauche : On échange la case vide avec la case à droite de celle-
ci. Si la case vide est tab[x][y] alors on l'échange avec tab[x+1][y].

Il faut ensuite s'assurer que le joueur soit limité par la taille de la grille pour
ses mouvements.

Il y a 4 cas de mouvements impossibles, N étant la taille du tableau :

* Si y=N alors on ne peut pas se déplacer vers le haut, la case vide est sur la
dernière ligne.
* Si y=1 alors on ne peut pas se déplacer vers le bas, la case vide est sur la
première ligne.
* Si x=1 alors on ne peut pas se déplacer vers la droite, la case vide est sur la
première colonne.
* Si x=N alors on ne peut pas se déplacer vers la gauche, la case vide est sur la
dernière colonne.

Avec ces règles, on peut se déplacer dans la grille selon les règles du jeu du Taquin.
A chaque déplacement, on vérifie si le jeu est résolu ou non grace à la fonction
verifTab. On affiche aussi la tableau à chaque déplacement.

## Fonction d'initialisation et de mélange de la grille de jeu

Il fallait une fonction qui puisse initialiser une grille de jeu et la mélanger de
sorte à ce que le jeu puisse être résolu. On part d'une grille déjà triée puis on
réalise des déplacements aléatoire pour la mélanger avec les fonctions rand et switch
dans le programme. Théoriquement puisqu'on part d'une grille déjà triée, le jeu peut
être résolu.

## Fonction de création d'une grille de jeu venant d'un fichier

Il fallait pouvoir gérer une grille venant d'un fichier extérieur au programme. Le nom
du fichier doit être "grilletaquin.txt" et la grille est sous la forme : (5 2 9 3 4 1
6...). La fonction recuptab consiste à créer en premier lieu un tableau de dimensions
demandées au préalable au joueur. Puis on parcourt le tableau de taquin et à chaque
itération on va pouvoir récupérer deux caractères. Si les deux sont différents du
caractère 'espace' alors on sait que c'est un nombre supérieur à 10 et on multiplie le
premier caractère -'0' par 10. Enfin on ajoute le deuxième -'0' on met le nombre
récupéré dans la case de tabTaquin et on refait un fgetc pour arriver à la prochaine
itération à un caractère. Si 1 seul des deux est différent du caractère 'espace' alors
on récupère le caractère -'0' et on le met dans la case de tabTaquin. De cette manière
une grille de jeu est initialisée et on peut y jouer.

## Fonction de vérification de la résolution possible de la grille fichier

Nous n'avons pas réussi à coder cette fonction donc il faut que le joueur fournisse
une grille qu'il puisse résoudre. Nous savons que 50% des grilles aléatoires ne
peuvent pas être résolues. Il faut que la somme du nombre de transposition utilisées
pour trier le tableau additionné au nombre de déplacement selon les règles de la case
vide de sa place initiale à sa plase finale soit paire.


## Choix mode de jeu et quitter le jeu

On a créé via des scanf un choix entre un jeu aléatoire créé par le programme, ou un
jeu qui vient d'une grille dans un fichier. Chaque ligne du fichier correspond à une
grille. On peut aussi choisir de quitter le jeu avec la touche 'q'. Cette option est
située dans la partie déplacement du code.

## Problèmes

Nous n'avons pas réussi à mettre en place la SDL pour faire notre programme. Nous
avons eu des problèmes concernant la prise en charge des touches du clavier (pour les
flèches de déplacemement). C'est pourquoi nous avons décidé d'utiliser uniquement les
touches 'h' 'b' 'd' 'g' et une fonction switch. La cause étant les cours en distanciel. 

## Exécution 

Pour lancer le jeu il suffit de le compiler puis de l'exécuter.
Les choix possibles sont ensuite proposés dans le programme.

