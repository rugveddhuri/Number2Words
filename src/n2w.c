/**
 * Title : Numbers to Words
 * Author: Rugved Dhuri
 * Date  : 25 May 2015
 */

#include <stdlib.h>
#include "../include/n2w.h"

int n2w(char *str) {

    int i, j, k,
        sign,
        error;

    int unit,
        tens,
        place = 0;

    char buff[50];

    char *text[4][10] = {{"Zero", "", "Twenty", "Thirty", "Forty", "Fifty",
                     "Sixty", "Seventy", "Eighty", "Ninty"},
                    {"", "One", "Two", "Three", "Four", "Five",
                     "Six", "Seven", "Eight", "Nine"},
                    {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
                     "Sixteen", "Seventeen", "Eighteen", "Nineteen"},
                    {"", "", "Hundered", "Thousand", "Lakh",
                     "Crore", "Million", "Billion", "Trillion"}};

    struct denomination *next = NULL;
    struct denomination *tmp  = NULL;

        i = 0;
        j = 0;
        k = 0;
        error = 0;

        while (str[i]==' ' || str[i]=='\t') {
            i++;
        }

        sign = 1;
        while(str[i]=='+' || str[i]=='-') {
            if(str[i]=='-') {
                sign *= -1;
            }
            i++;
        }
        while(str[i]=='0') {
            if (j == 0) {
                k = i;
                j = 1;
            }
            else {
                k++;
            }
            i++;
        }
        if(j == 1) {
            if(str[i]<'0' || str[i]>'9') {
                i = k;
            }
            j = 0;
        }

        k = 0;
        if(str[i]>='0' && str[i]<='9') {
            j = 1;
        }
        while(str[i]>='0' && str[i]<='9') {
            buff[k++] = str[i++];
        }
        if(j == 0)
            error = 2;   //Required digit before dot
        else
            j = 0;

        if(str[i]=='.') {
            j = k;
            buff[k++] = str[i++];
            while(str[i]>='0' && str[i]<='9') {
                buff[k++] = str[i++];
            }
            if(k == j+1) {
                k = j;
                error = 3;  //Required digit after dot
            }
            j = 0;
        }

        if(str[i]!=' ' && str[i]!='\t' && str[i]!='\0' && str[i]!='\n') {
            error = 4;     // setting parse or scan
        }

        while(str[i]==' ' || str[i]=='\t') {
            i++;
        }

        buff[k] = '\0';

    if(error != 0) {
        perror("Error: Not a Valid Number");
        buff[0] = '\0';
    }
/*
    printf("Sign: %d\n", sign);
    printf("|%s|\n",buff);
*/
    i = 0;
    while(buff[i] != '.' && buff[i] != '\0' && buff[i] != '\n') {
        i++;
    }

    if(buff[i] == '.') {
        if(buff[i+1] != '\0' && buff[i+1] != '\n') {
            tens = buff[i+1] - '0';
        }
        else {
            tens = 0;
        }
        if(buff[i+2] != '\0' && buff[i+2] != '\n') {
            unit = buff[i+2] - '0';
        }
        else {
            unit = 0;
        }
        if(tens > 0 || unit > 0) {
            tmp = (struct denomination *) malloc (sizeof (struct denomination));
            if(tmp == NULL) {
                error = 5;
            }
            else {
                tmp->tens = tens;
                tmp->unit = unit;
                tmp->place = -1;
                tmp->next = next;
                next = tmp;
            }
            tmp = (struct denomination *) malloc (sizeof (struct denomination));
            if(tmp == NULL) {
                error = 6;
            }
            else {
                tmp->tens = 0;
                tmp->unit = 0;
                tmp->place = place;
                tmp->next = next;
                next = tmp;
            }
        }
    }

    place++;
    i--;

    //j = 0;
    while(i >= 0) {
        if(i >= 0) {
            unit = buff[i--] - '0';
        }
        else {
            unit = 0;
        }
        if(i >= 0) {
            tens = buff[i--] - '0';
        }
        else {
            tens = 0;
            i--;
        }

        if(place == 2) {
            i++;
            tens = 0;
        }

        if(tens > 0 || unit > 0 || place == 1 || place == 5) {
            tmp = (struct denomination *) malloc (sizeof (struct denomination));
            if(tmp == NULL) {
                error = 7;
            }
            else {
                tmp->tens = tens;
                tmp->unit = unit;
                tmp->place = place;
                tmp->next = next;
                next = tmp;
            }
            //j = 1;
        }
        if(place == 5) {
            place = 1;
        }
        place++;
    }
/*
    if(j == 0) {
        tmp = (struct denomination *) malloc (sizeof (struct denomination));
        if(tmp == NULL) {
            error = 7;
        }
        else {
            tmp->tens = 0;
            tmp->unit = 0;
            tmp->place = 1;
            tmp->next = next;
            next = tmp;
        }
    }
*/
    //debug
    tmp = next;
    if(error == 0) {
    if(next != NULL) {
        if(sign == -1)
            printf("Minus ");
    }
    j = 0;
    while(next != NULL) {
/*
        //printf("|");
        printf("\n-- Node %d ----\n", i);
        printf(" Tens :%d\n", next->tens);
        printf(" Unit :%d\n", next->unit);
        printf(" Place:%d\n", next->place);
        printf("---------------\n");
*/
        if(next->tens == 0) {
            if(next->unit == 0) {
                if(next->place == 1 && next == tmp && next->next == NULL) {
                    printf("%s ", text[0][0]);
                }
                if(next->place == -1) {
                    printf("%s ", text[0][0]);
                }
            }
            else {
                printf("%s ", text[1][next->unit]);
            }
        }
        else if(next->tens == 1) {
            printf("%s ", text[2][next->unit]);
        }
        else {
            printf("%s ", text[0][next->tens]);
            if(next->unit > 0) {
                printf("%s ", text[1][next->unit]);
            }
        }

        if(next->place == -1) {
            printf("Paise");
        }
        else if(next->place == 0 && j == 0) {
            printf("and ");
        }
        else if(next->place == 1) {
            if(next->tens == 0 && next->unit == 1 && next == tmp) {
                printf("Rupee ");
            }else if(next->tens != 0 || next->unit != 0 || next != tmp || next->next == NULL) {
                printf("Rupees ");
            }else {
                j = 1;
            }
        }
        else {
            if(next->place > 1) {
                printf("%s ", text[3][next->place]);
            }
        }
        next = next->next;
    }
    }
    else {
        switch(error) {
            case 1: perror("");
        }
    }
    next = tmp;
    while(next != NULL) {
        tmp = next;
        next = next->next;
        free(tmp);
    }

    return 1;
}
