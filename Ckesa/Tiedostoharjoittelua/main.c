#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filebasics.h"
#define MAXLINE 150

int print_file(const char *filename)
{
    int i = 0;
    int c;
    FILE *f = fopen(filename,"r");
    if (!f){
        return -1;
    }
    while(1){
        c = fgetc(f);
        if (c ==EOF){
            return i;
        }
        printf("%c", c);
        i++;
   }
}

char *difference(const char* file1, const char* file2){

    FILE *f1 = fopen(file1,"r");
    FILE *f2 = fopen(file2,"r");
    char filebuff[MAXLINE];
    char filebuff2[MAXLINE];
    int var = 0;

    while (((fgets(filebuff, MAXLINE, f1)) && (fgets(filebuff2, MAXLINE, f2)))) {              
        var = strcmp(filebuff, filebuff2);
        if (var!=0){
            char *ret = malloc(sizeof(filebuff)+sizeof(filebuff2));
            strcpy(ret,filebuff);
            strcat(ret,"----\n");
            strcat(ret, filebuff2);
            return ret;
        } 
   }
   return NULL;
}



int main(void)
{
    printf("--- Printing file:\n");
    int t = print_file("testifile.c");
    if(t<0)
        printf("Opening failed!\n");

    printf("--- Printed %d characters\n", t);

    char* diff = difference("testifile.c", "testifile2.c");
    printf("\n--- Difference:\n");
    printf("%s", diff);

    free(diff);

    return 0;
}
