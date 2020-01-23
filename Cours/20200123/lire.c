#include <stdio.h>
#include <stdlib.h>

#include "tab.h"

struct tab read_integers(char *file){
  FILE *f;
  struct tab res;
  
  f = fopen(file, "r");
  fread(&res, 1, sizeof(struct tab), f);

  fclose(f);

  return res;
}


int main(int argc, char *argv[]){
  struct tab res = read_integers(argv[1]);
  int i;
  
  for(i=0; i<res.len; i++)
    printf("%d, ", res.nb[i]);
  printf("\n");
  
  return 0;
}
