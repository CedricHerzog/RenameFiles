#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char **argv){
  DIR * dirp;
  struct dirent * dp;
  char * needle;
  char * newName;

  dirp = opendir(argv[1]);
  if(dirp == NULL)
    return (EXIT_FAILURE);
  while((dp = readdir(dirp)) != NULL){
    needle = strstr(dp->d_name, argv[2]);
    if(needle != NULL){

      int sizeFile = strlen(dp->d_name);
      int sizeArg = strlen(argv[2]);
      int sizeNeedle = strlen(needle);

      printf("File found\n");
      newName = malloc((sizeFile - sizeArg)*sizeof(char));
      //If the searched word is at the beggining
      if(sizeNeedle == sizeFile){
	newName = dp->d_name + sizeArg*sizeof(char);
      }//If the searched word is at the end
      else if(sizeNeedle == sizeArg){
	for(int i=0;i<sizeFile-sizeNeedle;i++){
	  newName[i] = dp->d_name[i];
	}
      }//If the searched word is in the middle
      else{
	char * start;
	char * end;
	start = malloc((sizeFile-sizeNeedle)*sizeof(char));
	end = malloc((sizeNeedle-sizeArg)*sizeof(char));

	for(int i=0;i<sizeFile-sizeNeedle;i++){
	  start[i] = dp->d_name[i];
	}
	for(int i=0;i<sizeFile-sizeArg-strlen(start);i++){
	  end[i] = dp->d_name[i+sizeArg+strlen(start)];
	}
	newName = strcat(start, end);
      }
      
      printf("Original name: %s\n", dp->d_name);
      printf("New name: %s\n\n", newName);
      rename(dp->d_name, newName);
    }
  }
  closedir(dirp);
  return 0;
}
