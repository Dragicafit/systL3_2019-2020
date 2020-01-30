#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
  int fd = open("toto", O_RDONLY);
  int lg = 0, n;
  char s[10];

  if (fd<0) return -1;
  while((n=read(fd, s, 10)) > 0){
    lg  += n;
  }

  close(fd);
  if(n<0) return -1;
  printf("%d\n", lg);
  
  return 0;
}
