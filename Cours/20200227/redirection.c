#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
  printf("pid = %d\n", getpid());
  
  int fd = open("toto", O_WRONLY|O_CREAT|O_TRUNC, 0600);
  sleep(10);
  dup2(fd, 1);
  close(fd);
  fprintf(stderr, "redirection faite\n");

  sleep(10);
  
  printf("ceci est un test\n");

  return 0;
}
