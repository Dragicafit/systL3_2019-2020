#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buffer[100];
    int nb = 0;
    do {
        nb = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (nb<=0)
            return 0;
        write(STDOUT_FILENO, buffer, nb);
    } while (buffer[nb-1]!='\0' && buffer[nb-2]!='\4');
    return 0;
}
