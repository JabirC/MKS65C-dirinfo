#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

char * permissions(int digit);
char * makeSizeReadable(unsigned int size, char * buffer);
void stats (char * filename); // Prints out File Info
