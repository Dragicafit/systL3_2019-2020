#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tar.h"

int main(int argc, char *argv[]) {
    if (argc<2)
        return -1;

    FILE* fichier = fopen(argv[1],"r");
    if (fichier == NULL)
        return -1;

    while (!feof(fichier)&&)
    {
        struct posix_header hd;
        unsigned int filesize;
        fread(&hd, BLOCKSIZE, 1, fichier);
        sscanf(hd.size, "%o", &filesize);
        printf("%u %s\n", filesize, hd.name);
        fseek (fichier , (filesize + BLOCKSIZE - 1) >> BLOCKBITS , SEEK_CUR );
    }
    fclose(fichier);
    return 0;
}
