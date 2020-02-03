#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

int main(void){
  int i, j;
  
  for(i=0; i<1000; i++){
    for(j=0; j<1000; j++){
#ifdef APPEL_SYST
      close(open(".", O_RDONLY));
#else
      sin(atan(i));
#endif
    }
  }
}
