#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(void){
  if(open("missing_file", O_RDONLY)==-1){
    perror("open missing_file ");
    printf("errno = %d\tENOENT= %d\n", errno, ENOENT);
  }
  if(open("not_readable_file", O_RDONLY)==-1){
    perror("open not_readable_file");
    printf("errno = %d\tEACCES = %d\n", errno, EACCES);
  }
  return 0;
}
