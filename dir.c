#include "filemaster.h"
#include <dirent.h>
#include <sys/types.h>

int open_and_test(char * dir) {
    DIR * directory;
    directory = opendir(dir);
    if(directory){

           struct dirent * entry;
           char * directories[100];
           int numdirs = 0;
           char * files [1000];
           int numfiles = 0;

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
                 printf("%s\n", reigningchamp );
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

                 char tempFileName[100] = "";
                 strcat(tempFileName , dir);
                 strcat(tempFileName, "/");
                 strcat(tempFileName, reigningchamp);

                 stats(tempFileName);
                 strcpy(tempFileName, "");
           }
      }
    else{printf("Directory does not exist or cannot be opened.\n");}
    return 0;
}

int main() {
  printf("\n\nPRINTING OUT CONTENTS FROM '../MKS65C-dirinfo'\n");
  char * dir_name = "../MKS65C-dirinfo";
  open_and_test(dir_name);
  return 0;
}
