#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <libgen.h>
#include <sys/param.h>
#include <assert.h>
#include "tar.h"

char buf[BLOCKSIZE];

void myseek(int fd,unsigned int nblocks) {
  if (fd != 0) {
    int n = lseek(fd,nblocks<<BLOCKBITS,SEEK_CUR);
    if (n < 0) {
      perror("lseek");
      exit(1);
    }
  } else {
    // stdin doesn't accept seek (?!)
    for (int i = 0; i < nblocks; i++) {
      read(fd,buf,BLOCKSIZE);
    }
  }
}

void extract(int fd, struct posix_header hd,
             unsigned int filesize,
             unsigned int perm) {
  int out;
  int n;
  int rest;
  switch (hd.typeflag) {

  case REGTYPE:
  case AREGTYPE:
    out = open(hd.name, O_WRONLY|O_CREAT|O_TRUNC, perm);
    rest = filesize;
    while (rest > 0) {
      n = read(fd,buf,BLOCKSIZE);
      if (n < BLOCKSIZE) {
        fprintf(stderr,"unexpected EOF\n");
        exit(1);
      }
      write(out,buf,MIN(rest,BLOCKSIZE));
      /* TODO: check errors */
      rest = rest - BLOCKSIZE;
    }
    close(out);
    break;

  case DIRTYPE:
    mkdir(hd.name, perm);
    /* TODO: check errors */
    break;

  case SYMTYPE:
    symlink(hd.linkname, hd.name);
    /* TODO: check errors */
    break;

  default:
    fprintf(stderr,"Unsupported type %c\n",hd.typeflag);
    exit(1);
    break;
  }
}

void detar(int fd, int listing_only) {
  int n;
  // assert (sizeof(struct posix_header) == BLOCKSIZE);
  struct posix_header hd;
  unsigned int filesize = 0;
  unsigned int nblocks = 0;
  unsigned int perm = 0;
  char * type;

  while (1) {
    n = read(fd,&hd,BLOCKSIZE);
    if (n == 0) { fprintf(stderr, "No more blocks\n"); exit(0); }
    if (n < 0) { perror("read"); exit(1); }
    if (n < BLOCKSIZE) { fprintf(stderr, "Incomplete header read\n"); exit(1); }

    /* Arret si block rempli de zeros, et en particulier nom="" */
    if (hd.name[0]=='\0') {
      printf("done\n");
      exit(0);
    }

    /* Verification de magic number (facultatif).
       POSIX : magic = "ustar"
       OLDGNU : magic = "ustar  " */
    if (strncmp(hd.magic,"ustar",5)) {
      fprintf(stderr, "Unsupported magic: %s\n",hd.magic);
      exit(1);
    }

    /* Facultatif: verification de checksum */
    if (!check_checksum(&hd)) {
      fprintf(stderr, "Bad checksum: %s\n",hd.chksum);
    }

    sscanf(hd.mode,"%o",&perm);
    sscanf(hd.size,"%o",&filesize);
    /* Facultatif: calcul a l'avance du nombre de blocs */
    nblocks = (filesize + BLOCKSIZE - 1) >> BLOCKBITS;

    switch (hd.typeflag) {
    case REGTYPE:
    case AREGTYPE:
      type = "reg";
      break;
    case DIRTYPE:
      type = "dir";
      break;
    case SYMTYPE:
      type = "lnk";
      break;
    default:
      type = "oth";
      break;
    }

    printf("%s %o %9d (%5d blocks) %s\n",
           type, perm, filesize, nblocks, hd.name);

    if (listing_only) {
      myseek(fd,nblocks);
    } else {
      extract(fd,hd,filesize,perm);
    }
  }
}

int main(int argc, char **argv){
  int fd = 0;
  if (argc > 2) {
    fprintf(stderr, "Too many arguments!\n");
    exit(1);
  }
  if (argc == 2) {
    fd = open(argv[1],O_RDONLY);
    if (fd < 0) {
      perror("open");
      exit(1);
    }
  }
  /* Pour ne faire qu'un listing sans desarchiver,
     donner un autre nom au binaire, p.ex. listar */
  int listing_only = strncmp(basename(argv[0]),"detar",6);
  detar(fd,listing_only);
  exit(0);
}
