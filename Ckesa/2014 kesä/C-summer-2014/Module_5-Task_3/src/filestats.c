#include "filestats.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

/* Returns the line count in given file
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * The number of lines in file. */
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


/* Count the number of words in the file. Word has to include at least one
 * alphabetic character, and words are separated by whitespace.
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * number of words in the file */
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

/* Returns the most common character in the file. Only alphabetic characters
 * are counted.
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns: the most common character.*/
int most_common(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if(!f)
        return -1;
    
    size_t counts[127] = {0};
    int c;
    
    while(!feof(f))
    {
        c = fgetc(f);
        if(isalpha(c))
            counts[c]++;
    }
    fclose(f);
    
    size_t biggest_count = 0;
    char most_common = 0;
    for(c = 0; c < 127; c++)
    {
        if(counts[c] > biggest_count)
        {
            biggest_count = counts[c];
            most_common = c;
        }
    }
    return most_common;
}