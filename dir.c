#include "filemaster.h"
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

unsigned int dirSize(char * dir){
  DIR * directory;
  directory = opendir(dir);
  if(directory){
    struct dirent * entry;
    unsigned int dirFilesize= 0;
    while ((entry = readdir(directory))){
      if (entry -> d_type == DT_REG ){
          char tempPath[100] = "";
          strcpy(tempPath, dir);
          strcpy(tempPath, "/");
          strcpy(tempPath, entry->d_name);

          struct stat * s = malloc(sizeof(struct stat));
          stat(tempPath, s);
          dirFilesize += s -> st_size;
          free(s);
      }
    }
    return dirFilesize;
  }
  else return 0;
}

int open_and_test(char * dir) {
    DIR * directory;
    directory = opendir(dir);
    if(directory){
           struct dirent * entry;
           char * directories[1000];
           int numdirs = 0;
           char * files [1000];
           int numfiles = 0;
           unsigned int totalFileSize= 0;

           while ((entry = readdir(directory))){
             if (entry -> d_type == DT_DIR){
                 *(directories + numdirs) = entry-> d_name;
                 numdirs++;
             }
             else {
                 *(files + numfiles) = entry ->d_name;
                 numfiles++;
             }
           }

           int indexOfReigningChamp;
           printf("\n\nPRINTING OUT CONTENTS FROM '%s'\n", dir);
           printf("==================DIRECTORIES====================\n");
           for(int dirCount = 0; dirCount < numdirs; dirCount++){
                 char reigningchamp[100] = "~~~~";
                 for(int innerdirCount = 0; innerdirCount < numdirs; innerdirCount++){
                    if(strcmp(*(directories + innerdirCount) , reigningchamp ) < 0) {
                      strcpy(reigningchamp , *(directories + innerdirCount));
                      indexOfReigningChamp = innerdirCount;
                    }
                 }
                 strcpy(*(directories + indexOfReigningChamp), "~~~~");
                 char tempDirName[100] = "";
                 strcat(tempDirName , dir);
                 strcat(tempDirName, "/");
                 strcat(tempDirName, reigningchamp);
                 int totalDirSize = dirSize(tempDirName);
                 char strsize[10];
                 strcpy(strsize, makeSizeReadable(totalDirSize, strsize));

                 printf("%*s %s\n", 8, strsize, reigningchamp );
           }
           printf("\n==================FILES==========================\n");
           for(int fileCount = 0; fileCount < numfiles; fileCount++){
                 char reigningchamp[1000] ="~~~~";
                 for(int innerfileCount = 0; innerfileCount < numfiles; innerfileCount++){
                    if(strcmp(*(files + innerfileCount) , reigningchamp ) < 0) {
                      strcpy(reigningchamp , *(files + innerfileCount));
                      indexOfReigningChamp = innerfileCount;
                    }
                 }
                 strcpy(*(files + indexOfReigningChamp), "~~~~");

                 char tempPath[100] = "";
                 strcpy(tempPath, dir);
                 strcat(tempPath, "/");
                 strcat(tempPath, reigningchamp);
                 stats(tempPath);
           }
           char strSize[10];
           strcpy(strSize, makeSizeReadable(dirSize(dir), strSize));
           printf("\nTOTAL SIZE OF FILES IN '%s': %s\n", dir, strSize);
      }
    else{printf("errno: %d --- %s\n" , errno,  strerror(errno));}
    return 0;
}

int main(int argc, char *argv[]) {
  char dir_name[100];
  if(!argv[1]){
    printf("Please specify a directory: \n");
    scanf("%s", dir_name);
    }
  else strcpy(dir_name, argv[1]);
  open_and_test(dir_name);
  return 0;
}
