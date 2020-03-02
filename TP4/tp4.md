TP nº3 : synchronisation père-fils
=================================

**L3 Informatique - Système**

Ce TP traite de deux manières de synchroniser des processus
généalogiquement liés entre eux.  Les deux premiers exercices utilisent
la fonction `wait()` pour permettre au père de détecter la terminaison de
ses fils.  Les deux suivants utilisent des tubes nommés pour permettre
aux processus de communiquer, mais également de se synchroniser.

Dans chaque exercice, penser à ajouter les affichages nécessaires à la
bonne compréhension de l'exécution.

Exercice 1 : épinards
---------------------

Écrire un programme qui crée deux processus, un père et son fils. Le père
affiche d'abord le message `Mange tes épinards!`, auquel le fils répond
imperturbablement `Non!` un nombre aléatoire de fois, avant de finir par
céder et d'afficher `Oui pôpa...` et de terminer (son assiette). Le père
affiche alors `C'est bien, Popeye! Tu seras fort comme papa.` puis
termine lui aussi.


Exercice 2 : devinette
----------------------

Écrire un programme qui crée 10 processus, un père et ses fils. Chacun
tire une valeur aléatoire entre 1 et 100. Le père garde la sienne
secrète, tandis que les fils terminent en retournant leur tirage.  Le
père collecte les tirages de ses fils, puis annonce le vainqueur : le PID
du fils qui est le plus proche de sa valeur secrète.


Exercice 3 : ping-pong avec des tubes
-------------------------------------

Écrire un programme qui crée deux processus, un père et son fils, qui
communiquent par tube(s). Le père envoie `ping` à son fils, qui répond
`pong`, auquel cas le père répond à nouveau `ping`, etc. Au bout de quelques
échanges de balles, l'un des deux processus affiche sur la sortie
standard `Dehors, j'ai gagné!` puis termine. L'autre processus affiche
alors `Bravo... une petite revanche?` avant de terminer à son tour.
Combien faut-il de tubes?


Exercice 4 : la patate chaude
-----------------------------

Dans cet exercice, `N` processus `p1`, `p2`, `pN` forment un anneau :
`p1` est relié à `p2` par un tube, `p2` à `p3`, ..., et `pN` est relié à
`p1`.  Un jeton, ou patate chaude, circule dans cet anneau; c'est un
entier.

Chaque processus lit sur le tube qui le relie au processus précédent.
Quand il reçoit la patate chaude, il affiche un message du type `Mon PID
est 2048 et la patate vaut 17`, puis il incrémente la patate et la
transmet au processus suivant.

La ligne de commande doit récupérer deux paramètres : le premier est la
taille `N` de l'anneau, le deuxième est la valeur maximale de la patate
`patatmax`.

Il faut donc créer l'anneau et les tubes avant de lancer la patate
(initialisée à 0) dedans. Attention, une seule patate doit circuler!
Quand la patate atteint `patatmax`, le processus qui la reçoit doit
afficher `Argh ! Je meurs !` puis se terminer. Faire en sorte que les
autres processus détectent la fin de la partie et terminent également.
