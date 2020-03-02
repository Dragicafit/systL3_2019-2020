#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10

void writing(int fd, int t){
  char buf[LEN];
  sprintf(buf, "%d", getpid());
  while(1){
    write(fd, buf, strlen(buf));
    sleep(t);
  }
}

void display(int fd){
  char buf[LEN];

  memset(buf, 0, LEN);
  read(fd, buf, LEN);
  printf("lu sur %d : %s\n", fd, buf);
}

void reading(int fd1, int fd2){
  fd_set readfds;
  int max_fd=(fd1>fd2)?fd1:fd2;

  while(1){
    FD_ZERO(&readfds);
    FD_SET(fd1, &readfds);
    FD_SET(fd2, &readfds);
    select(max_fd+1, &readfds, NULL, NULL, NULL);
    if(FD_ISSET(fd1, &readfds)){
      display(fd1);
    }
    if(FD_ISSET(fd2, &readfds)){
      display(fd2);
    }
  }
}

int main(void){
  int pipefd1[2], pipefd2[2];

  if(pipe(pipefd1)==-1){
    perror("pipe1");
    exit(1);
  }

  if(pipe(pipefd2)==-1){
    perror("pipe2");
    exit(1);
  }

  switch(fork()){
  case -1: perror("fork");
    exit(1);
  case 0://ecrivain tube1
    close(pipefd2[0]);
    close(pipefd2[1]);
    close(pipefd1[0]);
    writing(pipefd1[1], 1);
    break;
  default:
    switch(fork()){
    case -1: perror("fork");
      exit(1);
    case 0://ecrivain tube2
      close(pipefd1[0]);
      close(pipefd1[1]);
      close(pipefd2[0]);
      writing(pipefd2[1], 2);
      break;
    default://lecteur
      close(pipefd1[1]);
      close(pipefd2[1]);
      reading(pipefd1[0], pipefd2[0]);
    }
  }
  
  return 0;
}
