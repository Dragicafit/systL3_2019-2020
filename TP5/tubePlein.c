#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void pass(int signal) {}

void install_handler() { signal(SIGUSR1, pass); }

void filling(int fd) {
    int n;
    for (int i = 0; 1; i++) {
        n = write(fd, "", 1);
        if (n < 0) {
            break;
        } else {
            printf("%d\n", i);
        }
    }
}

int main(void) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("ecrivain pid = %d\n", getpid());
    filling(pipefd[1]);
    printf("ecriture finie");
    close(pipefd[0]);
    close(pipefd[1]);
}
