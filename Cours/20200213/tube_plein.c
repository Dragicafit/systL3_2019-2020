#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define SIZE 30000

char buf[SIZE];

void pass(int signal){}

void install_handler(){
  signal(SIGUSR1, pass);
}

void filling(int fd){
  int n;
  while(1){
    n = write(fd, buf, SIZE);
    printf("ai ecrit %d caracteres\n", n);
  }
}

int main(void){
  int pipefd[2];
  int n;

  if(pipe(pipefd)==-1){
    perror("pipe");
    exit(1);
  }

  switch(fork()){
  case -1:
    perror("fork");
    exit(1);
  case 0://ecrivain
    close(pipefd[0]);
    printf("ecrivain pid = %d\n", getpid());
    filling(pipefd[1]);
    printf("ecriture finie");
    break;
  default://lecteur
    close(pipefd[1]);
    printf("lecteur pid = %d\n", getpid());
    install_handler();
    pause();
    n = read(pipefd[0], buf, SIZE);
    printf("ai lu %d caracteres\n", n);
    pause();
  }
}
