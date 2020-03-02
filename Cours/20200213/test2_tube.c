#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

char up(char c){
  return (c>='a' && c<='z') ? c+'A'-'a' : c;
}

int main(){
  int fd[2];
  pipe(fd);
  char c;
  int n;

  if(fork()==0){
    close(fd[0]);
    while(1){
      if(read(STDIN_FILENO, &c, sizeof(char))==0){
        close(fd[1]);
        exit(0);
      }
      write(fd[1], &c, sizeof(char));
    }
  } else {
    close(fd[1]);
    while(1){
      n = read(fd[0], &c, sizeof(char));
      if(n==0){
        close(fd[0]);
        exit(0);
      }
      c = up(c);
      write(STDOUT_FILENO, &c, sizeof(char));
    }
    close(fd[0]);
  }

}
