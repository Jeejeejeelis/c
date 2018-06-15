#include <stdio.h>
#include "filestats.h"
#include <ctype.h>

int line_count(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if(!f)
        return -1;
    
    char kirjaimia[100];
    int lines = 0;
    
    size_t read = fread(kirjaimia, 1, 100, f);
    if(read == 0)
        return 0;
    else
        lines++;
    for(size_t i = 0; i < read; i++)
    {
        if(kirjaimia[i] == '\n')
            lines++;
    }
    
    while(!feof(f))
    {
        size_t read = fread(kirjaimia, 1, 100, f);
        for(size_t i = 0; i < read; i++)
        {
            if(kirjaimia[i] == '\n')
                lines++;
        }
    }
    
    fseek(f, -1, SEEK_END);
    char last[1];
    fread(last, 1, 1, f);
    if(*last == '\n')
        lines--;
    
    fclose(f);
    return lines;
}

int word_count(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if(!f)
        return -1;
    
    char isWord = 0;
    int current;
    int count = 0;
    
    while(!feof(f))
    {
        current = fgetc(f);
        if(isalpha(current))
            isWord = 1;
        if(isspace(current) && isWord)
        {
            count++;
            isWord = 0;
        }
    }
    if(isWord)
        count++;
    fclose(f);
    return count;
}

int main(int argc, char *argv[])
{
    /* You can modify this file as needed, for example to test different
     * files. If you run on command line, this function optionally reads
     * the filename from command line, if one is included. */
    char *filename = "testi.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    
    printf("Line count: %d\n", line_count(filename));
    
    printf("Word count: %d\n", word_count(filename));

    return 0;
}
