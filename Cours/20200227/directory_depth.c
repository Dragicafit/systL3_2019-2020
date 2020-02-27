#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int depth(char *file){
  struct stat sb;
  int d = 0, d2;
  char *pwd;

  if(stat(file, &sb)==-1){
    perror("stat");
    exit(1);
  }

  if(S_ISDIR(sb.st_mode)){
    pwd = getcwd(NULL, 0);
    chdir(file);
    
    DIR *dirp = opendir(".");
    struct dirent *entry;
    
    while((entry=readdir(dirp))){
      if(strcmp(entry->d_name, ".")!=0 && strcmp(entry->d_name, "..")!=0){
        d2 = 1 + depth(entry->d_name);
        d = (d2>d) ? d2 : d;
      }
    }

    closedir(dirp);
    chdir(pwd);
    free(pwd);
  }
  
  return d;
}

int main(int argc, char** argv){
  printf("%d\n", depth((argc>1) ? argv[1] : "."));
  
  return 0;
}
