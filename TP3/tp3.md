TP nº3 : duplication de processus
=================================

**L3 Informatique - Système**


Exercice 1 : cacophonie
-----------------------

1. Écrire un programme qui crée deux processus : un père qui affiche
   100 fois `"ouaf!"` (sur la sortie standard), et un fils qui affiche
   100 fois `"miaou!"`. Interpréter l'affichage.
2. Écrire un programme muni d'une variable locale `n` qui crée deux
   processus : un père qui met `n` à 0, affiche 100 fois l'adresse et
   la valeur de `n` (sur la sortie standard), et un fils qui met `n` à
   1, et affiche 100 fois l'adresse et la valeur de `n`. Interpréter
   l'affichage.


Exercice 2 : généalogie imposée
-------------------------------

1. Écrire un programme qui crée la généalogie de processus suivante :

   ![](arbre_processus.png)

   Chaque processus doit afficher son pid et celui de son père, puis
   faire un appel à `pause()`. Vérifier (depuis un autre terminal) que
   la généalogie est bien celle attendue à l'aide de `ps` ou `pstree`
   avant de terminer les processus.

2. Modifier le programme pour que le processus "racine" initialise une
   variable `profondeur` à 0. Chaque processus doit ensuite utiliser
   `profondeur` pour préciser sa position dans l'arbre en affichant,
   en plus des pids, sa profondeur et celle de son père.


Exercice 3 : un peu de hasard
-----------------------------

1. Écrire un programme qui crée dix processus fils, dont chacun affiche son
   `pid` avant de terminer. Vérifier que votre programme n'affiche que dix
   lignes.

2. Modifier le programme pour que chaque fils attende un temps
   aléatoire (à l'aide des fonctions `random()` et `srandom()`) entre
   1 et 10 secondes, avant d'afficher son message et de mourir. Les
   fils ne devraient pas s'arrêter tous en même temps...


Exercice 4 : exécuter un programme deux fois
--------------------------------------------

Écrire un programme `twice` tel que `./twice cmd arg1 .. argn` exécute
deux fois la commande `cmd` avec ses arguments `arg1 .. argn`.


Exercice 5 : mélanger deux fichiers
-----------------------------------

Écrire un programme qui recopie le contenu de deux fichiers dans un troisième,
en les mélangeant; la recopie de chaque fichier devra être effectuée par un
processus différent---un père et son fils---, par paquets de 32 caractères.

Tester cette fonction, par exemple avec un fichier `fils` ne contenant
que des `' '` (espaces), et un fichier `pere` ne contenant que des `*`
(qui pourront être obtenus par une commande du type `head -c 10000
/dev/zero | tr '\0' ' '` ).


Exercice 6 : recherche dans un tableau
--------------------------------------

1. Écrire un programme qui crée un tableau de 512 cases contenant des
   entiers aléatoires entre 0 et 100, puis affiche tous les indices
   des cases de ce tableau dont la valeur est 33.

2. Modifier le programme pour qu'il utilise deux processus, le père
   qui parcourt la première moitié du tableau, et le fils qui parcourt
   la seconde.

3. Modifier à nouveau le programme pour partager le travail entre 2^k
   processus, où k est donné sur la ligne de commande.
