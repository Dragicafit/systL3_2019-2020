#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void inode_type(char *file){
  struct stat st;

  printf("%s: ", file);
  if(stat(file, &st)==-1){
    printf("does not exist or you do not have the rights to access it\n");
    return;
  }

  if(S_ISREG(st.st_mode)){
    printf("regular file");
  } else if (S_ISDIR(st.st_mode)){
    printf("directory");
  } else {
    printf("wtf?!?");
  }
  printf("\n");

  if( (st.st_mode & S_IRGRP) != 0){//attention a bien parentheser
    printf("droits en lecture pour le groupe\n");
  } else {
    printf("pas droits en lecture pour le groupe\n");
  }
}

int main(int argc, char **argv){
  int i;
  
  if(argc<2){
    fprintf(stderr, "%s usage: %s file1 [file2 ... fileN]\n", argv[0], argv[0]);
    exit(1);
  }

  for(int i=1; i<argc; i++){
    inode_type(argv[i]);
  }
  
  return 0;
}
