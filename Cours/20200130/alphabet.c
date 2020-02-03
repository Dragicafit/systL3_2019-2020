#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
  int fd = open("ALPHABET", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
  char c;
  int n;

  if (fd<0) return -1;
  for(c='a'; c<='z'; c++)
    if(write(fd, &c, 1)<0) return -1;

  close(fd);
  return 0;
}
