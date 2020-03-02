#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void f(){
  int n = 3;  //dans la pile
  int* t = malloc(3*sizeof(int)); // t dans la pile,
                                 // *t dans le tas
  printf("valeur de t : %p\n", &t);
  printf("contenu de t : %p\n", t);
}


int main(void){
  printf("pid = %d\n", getpid());
  f();
  pause();
  return 0;
}
