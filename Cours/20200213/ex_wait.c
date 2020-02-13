#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
  int r, w;

  r = fork();
  switch(r){
  case -1: perror("fork");
    exit(1);
  case 0: //fils
    printf("je suis le fils, mon pid est %d, celui de mon pere %d\n",
           getpid(), getppid());
    sleep(2);
    exit(42);
  default: //pere
    printf("je suis le pere de pid %d, je viens de creer un fils de pid %d\n",
           getpid(), r);
    wait(&w);
    printf("message recu: %d\n", WEXITSTATUS(w));
//    sleep(42);
  }

  return 0;
}
