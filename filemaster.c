#include "filemaster.h"


char * permissions(int digit){
  char * retval = malloc(10 * sizeof(char));
  switch (digit){
     case 0: strcpy(retval, "---");
            break;
     case 1: strcpy(retval, "--x");
            break;
     case 2: strcpy(retval, "-w-");
            break;
     case 3: strcpy(retval, "-wx");
            break;
     case 4: strcpy(retval, "r--");
            break;
     case 5: strcpy(retval, "r-x");
            break;
     case 6: strcpy(retval, "rw-");
            break;
     case 7: strcpy(retval, "rwx");
            break;
  }
  return retval;
}

char * makeSizeReadable(unsigned int size, char * buffer){
      int i = 0;
      double doubleSize = size * 1.0;
      const char* units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
      while (doubleSize >= 1024) {
          doubleSize /= 1024;
          i++;
      }
      sprintf(buffer, "%.*f%s", 1, doubleSize, units[i]);
      return buffer;
}

void stats (char * filename){
  struct stat * s = malloc(sizeof(struct stat));
  stat(filename, s);

  unsigned int size = s -> st_size;
  char strSize[10];
  strcpy(strSize, makeSizeReadable(size, strSize));

  int mode = s -> st_mode;
  mode = mode % 512;


  const long int timeinsec = (s -> st_atime) - 18000;
  struct tm * realtime = gmtime(&timeinsec);
  char * dayofweek = malloc(10 * sizeof(char));

  switch (realtime -> tm_wday)
 {
     case 0: strcpy(dayofweek, "Sun");
             break;
     case 1: strcpy(dayofweek, "Mon");
             break;
     case 2: strcpy(dayofweek, "Tue");
             break;
     case 3: strcpy(dayofweek, "Wed");
             break;
     case 4: strcpy(dayofweek, "Thur");
             break;
     case 5: strcpy(dayofweek, "Fri");
             break;
     case 6: strcpy(dayofweek, "Sun");
             break;
 }

  char * month = malloc(20 * sizeof(char));

  switch (realtime -> tm_mon)
 {
     case 0: strcpy(month, "Jan");
             break;
     case 1: strcpy(month, "Feb");
            break;
     case 2: strcpy(month, "Mar");
             break;
     case 3: strcpy(month, "Apr");
             break;
     case 4: strcpy(month, "May");
             break;
     case 5: strcpy(month, "Jun");
             break;
     case 6: strcpy(month, "Jul");
             break;
     case 7: strcpy(month, "Aug");
             break;
     case 8: strcpy(month, "Sep");
             break;
     case 9: strcpy(month, "Oct");
             break;
     case 10: strcpy(month, "Nov");
             break;
     case 11: strcpy(month, "Dec");
             break;
 }
  int dayofmonth = realtime -> tm_mday;

  int hour = realtime -> tm_hour;
  char hourstr[10];
  if (hour >= 10) sprintf(hourstr, "%d", hour);
  else sprintf(hourstr, "%d%d", 0,  hour);

  int min = realtime -> tm_min;
  char minstr[10];
  if (min >= 10) sprintf(minstr, "%d", min);
  else sprintf(minstr, "%d%d", 0,  min);

  int sec = realtime -> tm_sec;
  char secstr[10];
  if (sec >= 10) sprintf(secstr, "%d", sec);
  else sprintf(secstr, "%d%d", 0,  sec);

  int year = realtime -> tm_year + 1900;

  char * firstperm = permissions(mode / 64 );

  char * secondperm =  permissions((mode / 8)%8);

  char * thirdperm = permissions(mode%8);



  printf("-%s%s%s 1 ", firstperm, secondperm, thirdperm );
  printf("%*s ",8, strSize); // "*" in between print types are for aligning the print results
  printf("%*s %*s %*d %*s:%*s:%*s %*d %s\n", 4, dayofweek, 3, month, 2, dayofmonth, 2, hourstr, 2, minstr, 2, secstr, 4, year, strrchr(filename, 47) + 1);

  free(s);
}
