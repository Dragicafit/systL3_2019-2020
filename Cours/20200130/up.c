#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char up(char c){
  return (c>='a' && c<='z') ? c+'A'-'a' : c;
}

int main(void){
  int fd = open("toto", O_RDONLY);
  char c;
  int n;

  if (fd<0) return -1;
  while((n=read(fd, &c, 1)) > 0){
    printf("%c", up(c));
  }

  close(fd);
  if(n<0) return -1;
  printf("\n");
  
  return 0;
}
