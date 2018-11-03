#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>


void prnt_dir(int dirs, int files, char * dir_stream) {
    char only_dirs[dirs];
    char file_holder[files];

    DIR * d = opendir(dir_stream);
    struct dirent * entry;
    struct stat duf;

    entry = readdir(d);

    while(entry) {
        stat(entry->d_name, &duf);
        printf("%o\t%s\t%s\t%i\t%s\t%s\n", duf.st_mode % 512, duf.st_uid, duf.st_gid, duf.st_size, ctime(&(duf.st_ctime)), entry->d_name);
        entry = readdir(d);
    }
}


int open_and_test(char * dir) {
    DIR * d;
    d = opendir(dir);
    int dir_nums = 0;
    int files = 0;
    struct dirent * entry;

    entry = readdir(d);
    
    while (entry) {
        if (entry->d_type == DT_DIR) {
            dir_nums += 1;
        }else{
            files += 1;
        }
        entry = readdir(d);
    }
    prnt_dir(dir_nums, files, dir);

    return 0;
}






int main() {
  char * dir_name = "../MKS65C-dirinfo";
  open_and_test(dir_name);
  return 0;
}
