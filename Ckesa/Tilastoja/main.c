#include <stdio.h>
#include "filestats.h"
#include <ctype.h>

int line_count(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if(!f){
        return -1;
    }
    int merkki = 0;
    int lines=0;

    if (isalpha((fgetc(f)))){
        lines++;
    }

    fseek(f,0,SEEK_SET);

    while(!feof(f)){
        merkki = fgetc(f);
        if(merkki == '\n'){
            lines++;
        }
    }
    

    fclose(f);
    return lines;
}

int word_count(const char *filename)
{
    char sana = 0;
    int merkki;
    int i = 0;
    FILE* f = fopen(filename, "r");
    
    if(!f){
        return -1;
    }

    while(!feof(f)){
        merkki = fgetc(f);
        if(isalpha(merkki))
            sana = 1;

        if(isspace(merkki) && sana){
            i++;
            sana = 0;
        }
    }
    if(sana){
        i++;
    }
    fclose(f);
    return i;
}

