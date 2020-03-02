TP nº5 : `select()`
=================================

**L3 Informatique - Système**

Ce TP traite de la gestion de plusieurs descripteurs des fichiers avec
`select()`, ce qui est souvent indispensable dans le contexte des applications
réseaux. On verra aussi comment utiliser `select()` pour effectuer des
lectures/écritures non bloquantes.


Exercice 1 : volume d'un tube
------------------------------

- Que se passe-t-il en cas de lecture dans un tube vide? Le déterminer
  expérimentalement.

- Que se passe-t-il en cas d'écriture dans un tube plein? Déterminer
  expérimentalement la taille du tampon d'un tube, en le remplissant
  progressivement et en affichant où on en est au fur et à mesure.


Exercice 2 : pas de bouchons
-----------------------------

À l'aide de `select()`, modifier les programmes développés pour l'exercice 1
pour *prévenir* les blocages. Avant chaque lecture et écriture, vérifier
systématiquement avec `select()` si l'action serait possible sans blocage, et
terminer l'exécution avec un message d'erreur pertinent si ce n'est pas le cas.

Faites attention à :

- bien réinitialiser les paramètres de `select()` avant chaque appel
- initialiser la structure `timeout` pour faire en sorte que `select` ne bloque
  pas.


Exercice 3 : il y a de l'écho
-----------------------------

Écrire un programme `echo-service.c` dont le processus principal
implémente un service d'écho : il reçoit (en boucle infinie) des messages
de la part de son (seul) processus fils via un tube, et les affiche sur
la sortie standard, préfixés par le PID du processus fils.

Le processus fils exécute une boucle infinie qui, à chaque itération, attend un
temps aléatoire entre 0 et 5 secondes et ensuite envoie au processus père le
message `"YAWN, j'ai dormi X seconde(s), ça va?"` via le tube.


Exercice 4 : cacophonie
-----------------------

Modifier le programme `echo-service.c` de l'exercice 3 pour supporter
plusieurs processus fils, qui écrivent chacun *via* un tube dédié, partagé
avec le processus père.  Le nombre de processus fils doit être spécifié
*via* la ligne de commande.

Essayer d'abord une implémentation naïve, dans laquelle le processus père
traite les requêtes des fils une par une, dans un ordre prédéfini (p.ex.,
l'ordre de création des processus). Vérifier le débit (*throughput*),
c.à.d. le nombre de lignes affichées sur la sortie standard par unité de
temps par le processus père (p.ex., avec le filtre UNIX `pv` et son
option `--line-mode`, ou alors en le mesurant vous-même dans le processus
père).  Comment le débit change-t-il quand on augmente le nombre de
processus fils?

Essayer ensuite une implémentation de la gestion des requêtes basé sur
`select()`, dans laquelle les requêtes sont traitées dès qu'ils arrivent
(et le père est disponible pour les traiter). Quel est le débit et
comment est-il impacté par le nombre de processus fils?
