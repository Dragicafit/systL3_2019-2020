TP nº1 : archives tar
=====================

**L3 Informatique - Système**

L'objectif de ce TP est de programmer un outil permettant de lire et écrire des archives `tar`.

On rappelle que `tar` est un outil d'archivage, permettant par exemple les usages suivants :

```bash
tar cf test.tar fichier1 ... fichierN      # création d'une archive test.tar
tar tvf test.tar                           # liste des fichiers contenus dans test.tar
tar xf test.tar                            # extraction des fichiers présents dans test.tar
```

Note : par défaut, une archive `tar` n'est pas compressée, mais il suffit d'utiliser dessus un outil de compression tel que `gzip` pour obtenir des archives compressées `*.tar.gz`, souvent aussi nommées `*.tgz`. L'outil `tar` peut directement faire cela, voir par exemple `tar czf`. Dans ce TP nous ne travaillerons qu'avec des archives `tar` *non compressées*.

#### Le format des archives tar

Il existe plusieurs variantes de `tar`, elles-mêmes avec un certain nombre d'extensions possibles. Ce qui suit devrait suffire à pouvoir lire la plupart des fichiers `.tar`, et à écrire des `.tar` acceptés par la plupart des utilitaires `tar`.

Un fichier `tar` est une suite de blocs de 512 octets. S'il représente une archive des fichiers `f1`, ..., `fn`, alors ce fichier `tar` comporte, dans l'ordre :
 
  - un bloc entête pour `f1`
  - les blocs correspondant au contenu de `f1`
  - ...
  - un bloc entête pour `fn`
  - les blocs correspondant au contenu de `fn`
  - deux blocs finaux formés uniquement de zéros

Si la taille d'un des fichiers archivés `fi` n'est pas un multiple de 512, alors le dernier bloc concernant `fi` est complété avec des octets nuls `'\0'` à hauteur de 512 octets. 

Un bloc entête a une structure décrite par le type `struct posix_header` dans le fichier [tar.h](tar.h) fourni. Notez que cette structure fait exactement 512 octets de long (macro `BLOCKSIZE`), afin de correspondre exactement à la lecture (ou à l'écriture) d'un bloc. Voici quelques mots sur les principaux champs, les autres pouvant être ignorés ici :

  - `char name[100]` : nom long du fichier (_ie_ sa référence relative au point d'archivage). On supposera ici que 100 caractères suffisent pour stocker ce nom. Les caractères inutilisés seront mis à `'\0'`.
  
  - `char mode[8]` : permissions du fichier, converties en entier. Comme pour tous les autres champs numériques de l'entête, le dernier caractère est un `'\0'`, et les autres des caractères-chiffres entre `'0'` et `'7'` représentant un entier en octal. Comme vous ne savez pas encore manipuler les droits d'un fichier, ce champ sera ignoré à la lecture, et à l'écriture il sera rempli arbitrairement par `sprintf(hd.mode,"0000700")`.
  
  - `char size[12]` : taille du fichier. Même remarque que précédemment concernant le codage de ce nombre, mais cette fois sur 12 caractères au lieu de 8. La lecture pourra se faire par `sscanf(hd.size,"%o",...)` et l'écriture par `sprintf(hd.size,"%011o",...)`.
  
  - `char chksum[8]` : empreinte ("checksum") de ce bloc entête. À la lecture, vous pouvez l'ignorer. En revanche, pour fabriquer un `tar` acceptable par GNU `tar` ce champ doit être correct. Pour cela, utiliser la fonction fournie `set_checksum()` de `tar.h` une fois que votre entête est prête. Pour plus de détail, voir le commentaire devant `set_checksum()`.

  - `char typeflag` : il vaut `'0'` (ou `'\0'`) pour un fichier standard. À l'extraction, il faudra donc ignorer les fichiers ayant un autre type.
 
  - `char magic[6]` : pour le format de `tar` que l'on utilise ici, ce champ devra être mis à `"ustar"` (macro `TMAGIC`), et le champ suivant `version` être à `"00"` (sans terminateur). En revanche les `tar` créés par GNU `tar` auront par défaut un magic un peu plus long `"ustar  "` (avec deux blancs à la fin).


#### Exercice 1 : liste des fichiers contenus dans une archive `tar`

Écrire un programme `listar` affichant du contenu d'une archive `tar` dans l'esprit de `tar tvf` (mais avec seulement l'affichage de la taille et du nom de fichier). Pour cela, utiliser un tampon de 512 octets pour lire les blocs les uns après les autres.

Pour vous déplacer d'entête en entête dans le fichier `tar`, vous pouvez remarquer que le nombre de blocs occupés par un fichier de taille `filesize` est la partie entière _supérieure_ de la division de `filesize` par 512, c'est-à-dire `(filesize + 512 - 1) / 512`, ou encore `(filesize + 512 - 1) >> 9` puisque 512 = 2^9, ou `(filesize + BLOCKSIZE - 1) >> BLOCKBITS` avec les macros définies dans `tar.h`.


#### Exercice 2 : extraction des archives "plates"

Écrire un programme `detar` extrayant les fichiers ordinaires contenus dans une archive `tar`. On supposera qu'aucune création de répertoires n'est nécessaire.

Attention! L'extraction d'une archive peut écraser des fichiers déjà présents. De plus vos premiers essais d'extracteur de `tar` peuvent mal se comporter (par exemple créer des millions de fichiers aux noms cabalistiques). Il est donc *impératif* de faire vos essais dans un sous-répertoire de test ne contenant rien d'important, pas même vos fichiers C. Se placer dans `/tmp` est un bon choix.

#### Exercice 3 : création d'une archive simple

Écrire un programme `mktar` tel que l'appel à `mktar archive.tar f1 ... fn` crée l'archive `archive.tar` contenant les fichiers ordinaires `f1` ... `fn` (situés dans le répertoire courant). Ce fichier `archive.tar` devra pouvoir être lu avec l'utilitaire GNU `tar`.

Pour déterminer la taille d'un fichier, une solution consiste à utiliser les fonctions `fseek()` (pour se placer à la fin du fichier) et `ftell()`.

#### Exercice 4 : extraction d'un fichier particulier

Modifier `detar` pour qu'il puisse prendre un (ou des) arguments supplémentaires, et que dans ce cas il n'extraie de l'archive que les fichiers dont les noms ont été passés en paramètre.

#### Exercice 5 : modification de l'archive

* Écrire un programme `addtar` tel que `addtar archive.tar f1 ... fn` ajoute les fichiers `f1` ... `fn` à l'archive (sans vérifier s'ils s'y trouvent déjà).

* Écrire un programme `deltar` tel que `deltar archive.tar f1 ... fn` supprime les fichiers `f1` ... `fn` de l'archive.

