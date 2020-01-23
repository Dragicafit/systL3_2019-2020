/* recopie du poly de Juliusz Chroboczek */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

int main(int argc, char **argv) {
  int fd1, fd2, rc1, rc2;
  char buf[SIZE];
  
  if(argc != 3) {
    fprintf(stderr, "Syntaxe: %s f1 f2\n", argv[0]);
    exit(1);
  }

  fd1 = open(argv[1], O_RDONLY);
  if(fd1 < 0) {
    perror("open(fd1)");
    exit(1);
  }
  
  fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if(fd2 < 0) {
    perror("open(fd2)");
    exit(1);
  }
  
  while(1) {
    rc1 = read(fd1, buf, SIZE);
    if(rc1 < 0) {
      perror("read");
      exit(1);
    }

    if(rc1 == 0)
      break;
  
    rc2 = write(fd2, buf, rc1);
    if(rc2 < 0) {
      perror("write");
      exit(1);
    }
    if(rc2 != rc1) {
      fprintf(stderr, "Ecriture interrompue");
      exit(1);
    }
  }
  
  close(fd1);
  close(fd2);
  return 0;
}
