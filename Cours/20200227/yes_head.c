#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
  int fd[2];
  
  if(pipe(fd)==-1){
    perror("pipe");
    exit(1);
  }

  switch(fork()){
  case -1: perror("fork");
    exit(1);
  case 0:// head [lecteur]
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    execlp("head", "head", NULL);
    break;
  default:// yes [ecrivain]
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    execlp("yes", "yes", NULL);
  }
}
