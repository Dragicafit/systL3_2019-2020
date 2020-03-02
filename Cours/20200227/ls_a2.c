#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

int ls(char *file){
  struct stat sb;

  if(stat(file, &sb)==-1){
    perror("stat");
    exit(1);
  }

  if(S_ISDIR(sb.st_mode)){
      DIR *dirp = opendir(file);
      struct dirent *entry;
  
      while((entry=readdir(dirp))){
        printf("%s\n", entry->d_name);
      }

      closedir(dirp);
  } else {
    printf("%s\n", file);
  }
}

int main(int argc, char **argv){
  ls((argc>1) ? argv[1] : ".");
  
  return 0;
}
