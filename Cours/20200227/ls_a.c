#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int ls(char *dir){
  DIR *dirp = opendir(dir);
  struct dirent *entry;
  
  while((entry=readdir(dirp))){
    printf("%s\n", entry->d_name);
  }

  closedir(dirp);
}

int main(){
  ls(".");
  
  return 0;
}
