#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

int main(void){
  int fd[2];
  long int n;

  //signal(SIGPIPE, SIG_IGN);
  
  pipe(fd);
  close(fd[0]);

  n = write(fd[1], "c", sizeof(char));
  printf("n = %ld\terrno = %d \n", n, errno);
  
  return 0;
}
