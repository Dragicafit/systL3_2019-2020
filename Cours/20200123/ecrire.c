#include <stdio.h>
#include <stdlib.h>

#include "tab.h"

void write_integers(char *file, struct tab *res){
  FILE *f;
  
  f = fopen(file, "w");
  fwrite(res, 1, sizeof(struct tab), f);

  fclose(f);
}


int main(int argc, char *argv[]){
  int i;
  struct tab res;

  res.len = 6;
  for(i=0; i<res.len; i++)
    res.nb[i] = 2*i-1;

  write_integers(argv[1], &res);
  
  return 0;
}
