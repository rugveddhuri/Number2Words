#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/n2w.h"

int main(int argc, char *argv[])
{
    int i = 0;
    char str[50];

    if(argc > 1) {
        i = 1;
        while(i < argc) {
            n2w(argv[i++]);
            printf("\n");
        }
    }else {
        printf("Enter Number:");
        gets(str);
        n2w(str);
    }

    return EXIT_SUCCESS;
}
