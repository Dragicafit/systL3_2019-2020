#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tar.h"

char buf[BLOCKSIZE];

/* avance jusqu'à l'entête suivante */
void next_header(FILE *f, unsigned int filesize) {
  unsigned int nblocks = (filesize + BLOCKSIZE - 1) >> BLOCKBITS;
  for (int i = 0; i < nblocks; i++) {
     fread(buf, BLOCKSIZE, 1, f);
  }
}

/* lit une entête et retourne la taille du fichier correspondant
 * ou -1 si entête nulle */
int read_header(FILE * f) {
  struct posix_header hd;
  unsigned int filesize = 0, perm = 0;

  int nb = fread(&hd, BLOCKSIZE, 1, f);
  /* erreurs à traiter */
    
  /* Arrêt si bloc rempli de zéros, et en particulier nom="" */
  if (hd.name[0] == '\0') return -1;

  /* la taille et les droits */
  sscanf(hd.size, "%o", &filesize);
  sscanf(hd.mode, "%o", &perm);
    
  /* affichage  (droits en octal, taille en décimal, nom) */
  printf("%o\t%d\t%s\n", perm, filesize, hd.name);

  return filesize;
}


int main(int argc, char **argv){
  FILE *f;
  int filesize = 0;

  if (argc != 2) {
    fprintf(stderr, "Usage : %s toto.tar\n", argv[0]);
    exit(1);
  }
   
  /* ouverture du fichier tar */
  f = fopen(argv[1], "r");

  if (f ==  NULL) {
    perror("fopen");
    exit(1);
  }

  /* boucle principale */
  while (1) { 
    filesize = read_header(f);
    if (filesize == -1) break;
    next_header(f, filesize);
  }

  /* fermeture du fichier tar */
  fclose(f);

  exit(0);
}
