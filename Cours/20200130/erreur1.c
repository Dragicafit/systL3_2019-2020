#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void){
  if(open("missing_file", O_RDONLY)==-1){
    perror("open missing_file ");
  }
  if(open("not_readable_file", O_RDONLY)==-1){
    perror("open not_readable_file");
  }
  return 0;
}
