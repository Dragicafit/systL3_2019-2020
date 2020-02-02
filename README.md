Systèmes L3 2019-2020
=================

**Conseil :** cloner ce dépôt pour pouvoir récupérer les fichiers fournis avec un simple `git pull`, et travailler directement dans le répertoire cloné.

```bash
git clone git@gaufre.informatique.univ-paris-diderot.fr:klimann/systL3_2019-2020.git
```

# Équipe pédagogique

| | | |
|---:|---|---|
| amphi | Ines Klimann | klimann@irif.fr |
| TP groupe 1 | Stefano Zacchiroli | stefano.zacchiroli@irif.fr |
| TP groupes 2+4 | Dominique Poulalhon | dominique.poulalhon@irif.fr |
| TP groupes 3+MI | Claude Stolze | claude.stolze@irif.fr |

# Cours

#### 23/01/2020

* présentation globale du cours
* disgression de programmation autour des tampons; sources associés :
  [copie_inefficace.c](Cours/20200123/copie_inefficace.c),
  [copie_plus_efficace.c](Cours/20200123/copie_plus_efficace.c), [tab.h](Cours/20200123/tab.h),
  [ecrire.c](Cours/20200123/ecrire.c), [lire.c](Cours/20200123/lire.c)


#### 30/01/2020

* processus : mode noyau / mode utilisateur
* fichiers : i-nœuds sur disque et en mémoire, `open`, `close`, `read`, `write`; sources : [comparaison_temps.c](Cours/20200130/comparaison_temps.c), [up.c](Cours/20200130/up.c), [wc.c](Cours/20200130/wc.c), [alphabet.c](Cours/20200130/alphabet.c)
* gestion des erreurs : `perror`, `errno`; sources : [erreur1.c](Cours/20200130/erreur1.c), [erreur2.c](Cours/20200130/erreur2.c)

# TP

* TP nº1 (tampons et archivage) : [énoncé](TP1/tp1.md) + (exceptionnellement) correction du premier exercice en [haut-niveau](TP1/listar_haut_niveau.c) et [bas-niveau](TP1/listar_bas_niveau.c) pour vous aider à avancer

**Remarque :** ces feuilles de TD en *markdown* sont faites pour être lues directement sur l'interface web du gitlab de l'UFR. On profite ainsi de la coloration syntaxique, des liens hypertextes, etc. Mais la syntaxe markdown étant assez légère, ces feuilles de TD peuvent être ouvertes dans votre éditeur de texte favori.
