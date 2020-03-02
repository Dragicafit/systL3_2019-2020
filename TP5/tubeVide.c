#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 30000

char buf[SIZE];

void pass(int signal) {}

void install_handler() { signal(SIGUSR1, pass); }

int main(void) {
  int pipefd[2];
  int n;

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(1);
  }

  close(pipefd[1]);
  printf("lecteur pid = %d\n", getpid());
  install_handler();
  n = read(pipefd[0], buf, SIZE);
  printf("ai lu %d caracteres\n", n);
  close(pipefd[0]);
}
