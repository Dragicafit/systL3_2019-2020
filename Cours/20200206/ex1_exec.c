#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
  printf("mon pid : %d\n", getpid());
  execl("/usr/bin/xeyes", "toto", NULL);
}
