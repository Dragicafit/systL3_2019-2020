#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
  int r;

  r = fork();
  switch(r){
  case -1: perror("fork");
    exit(1);
  case 0: //fils
    printf("je suis le fils, mon pid est %d, celui de mon pere %d\n",
           getpid(), getppid());
    break;
  default: //pere
    printf("JE SUIS LE PERE DE PID %d, JE VIENS DE CREER UN FILS DE PID %d\n",
           getpid(), r);
  }

  return 0;
}
