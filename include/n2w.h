#ifndef N2W_H
 #define N2W_H
 #ifndef _STDIO_H_
  #include <stdio.h>
 #endif
 #ifndef _STDLIB_H_
  #include <stdlib.h>
 #endif

#define BUFF_SIZE 50

struct denomination {
    int unit;
    int tens;
    int place;
    struct denomination *next;
};

int n2w(char *str);

#endif
