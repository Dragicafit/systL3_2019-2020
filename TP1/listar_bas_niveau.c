#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "tar.h"

char buf[BLOCKSIZE];

/* avance jusqu'à l'entête suivante */
void next_header(int fd, unsigned int filesize) {
  unsigned int nblocks = (filesize + BLOCKSIZE - 1) >> BLOCKBITS;
  for (int i = 0; i < nblocks; i++) {
     int nb = read(fd, buf, BLOCKSIZE);
     /* erreurs à traiter */
  }
}

/* lit une entête et retourne la taille du fichier correspondant
 * ou -1 si entête nulle */
int read_header(int fd) {
  struct posix_header hd;
  unsigned int filesize = 0, perm = 0;

  int nb = read(fd, &hd, BLOCKSIZE);
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
  int fd;
  int filesize = 0;

  if (argc != 2) {
    fprintf(stderr, "Usage : %s toto.tar\n", argv[0]);
    exit(1);
  }
   
  /* ouverture du fichier tar */
  fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    perror("open");
    exit(1);
  }

  /* boucle principale */
  while (1) { 
    filesize = read_header(fd);
    if (filesize == -1) break;
    next_header(fd, filesize);
  }

  /* fermeture du fichier tar */
  close(fd);

  exit(0);
}
