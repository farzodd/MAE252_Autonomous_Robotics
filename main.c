#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ftw.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h> 

void printIndent(int i){
  for(int j = 0; j < i; ++j)
    printf("  ");
}

int dirRecurse(char *path, int indent, char *output, char *searchTerm){
  struct dirent *d;
  DIR *dp;

  int dindent = indent;
  
  char tempPath[1000];
  char *debugTracker = tempPath;
  strcpy(tempPath, path);
  // check if path is a directory
  if((dp = opendir(path)) == NULL){
    return 0;
  }

  // start constructing path
  while(d = readdir(dp)){
    strcpy(tempPath, path);
    if(d->d_ino != 0 && strcmp(d->d_name, ".") && strcmp(d->d_name, "..")){
      // init path so it clears
      printIndent(indent);
      printf("%s\n", d->d_name);
      // construct path
      strcat(tempPath, "/");
      strcat(tempPath, d->d_name);

      // check if file name is the search term
      if(!strcmp(d->d_name, searchTerm)){
	      strcat(output, "\nfound at: ");
	      strcat(output, tempPath);
      }
      // test if directory
      dirRecurse(tempPath, indent+1, output, searchTerm);
    }
  }
}

int main(int argc, char *argv[])
{
  // check if given valid argument
  // if not root is default directory
  char path[1000] = "";
  if(argc == 1)
    return 1;

  strcpy(path, argv[1]);

  char output[1000];

  char searchTerm[1000];
  strcpy(searchTerm, "my1.dat");
  printf("searching for %s\n", searchTerm);

  
  int ret = dirRecurse(path, 0, output, searchTerm);
  if(!strcmp(output, "")){
    strcpy(output, "file not found");
  }
  printf("file location: %s\n", output);
  return ret;
}
