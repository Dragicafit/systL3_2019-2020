#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <libgen.h>
#include <sys/param.h>
#include "tar.h"

char zeros[BLOCKSIZE] = {0};
char buf[BLOCKSIZE];

void tar_one_file(int fd, char * filename) {
  int n;
  // assert (sizeof(struct posix_header) == BLOCKSIZE);
  struct posix_header hd;
  struct stat st;

  memset(&hd,0,BLOCKSIZE);
  lstat(filename,&st);

  strcpy(hd.name,filename); /* TODO: check size, eviter strcpy */
  /* sprintf(hd.mode,"%07o",st.st_mode & 0777); */
  sprintf(hd.mode,"0000700");    // en dur puisqu'ils ne connaissent pas stat
  /* suppression... ça n'affecte pas la compatibilité avec gnu tar */
  // sprintf(hd.uid,"%07o",st.st_uid); /* gnu tar : non-critique */
  // sprintf(hd.gid,"%07o",st.st_gid); /* gnu tar : non-critique */
  // sprintf(hd.mtime,"%011lo",st.st_mtime); /* gnu tar : non-critique */
  if (S_ISDIR(st.st_mode)) {
    hd.typeflag = '5';
    sprintf(hd.size,"%011o",0);
  }
  if (S_ISLNK(st.st_mode)) {
    hd.typeflag = '2';
    readlink(filename,hd.linkname,99);
    sprintf(hd.size,"%011o",0);
  }
  if (S_ISREG(st.st_mode)) {
    hd.typeflag = '0';
    sprintf(hd.size,"%011lo",st.st_size);
  }
  strcpy(hd.magic, TMAGIC); /* gnu tar : non-critique */
  strcpy(hd.version, TVERSION); /* gnu tar : non-critique */
//  strcpy(hd.uname, "someone"); /* gnu tar : non-critique */
//  strcpy(hd.gname, "somegrp"); /* gnu tar : non-critique */

  /* calcul du checksum : indispensable pour gnu tar :-( */
  /* Code qu'on fournit dans tar.h */
  set_checksum(&hd);

  n = write(fd,&hd,BLOCKSIZE);
  if (n < 0) {
    perror("write");
    exit(1);
  }

  if (S_ISREG(st.st_mode)) {
    int input = open(filename,O_RDONLY);
    while ((n=read(input,buf,BLOCKSIZE)) == BLOCKSIZE) {
      write(fd,buf,BLOCKSIZE);
    }
    if (n!=0) {
      write(fd,buf,n);
      write(fd,zeros,BLOCKSIZE-n);
    }
    close(input);
  }
}

int main(int argc, char **argv){
  if (argc < 2) {
    fprintf(stderr, "Too few arguments!\n");
    exit(1);
  }
  int fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0644);
  if (fd < 0) {
    perror("open");
    exit(1);
  }
  for (int i=2; i<argc; i++) {
    tar_one_file(fd,argv[i]);
  }
  // finalize : deux blocs vides
  write(fd,zeros,BLOCKSIZE);
  write(fd,zeros,BLOCKSIZE);
  close(fd);
  exit(0);
}
