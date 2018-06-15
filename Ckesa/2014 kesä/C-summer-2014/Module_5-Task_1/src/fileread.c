#include "fileread.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Prints the given file as text on the screen.
 * Only printable characters are shown. Non-printable characters are printed
 * as '?'. <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int textdump(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if(!f)
        return -1;
    
    char buffer[100];
    int read_total = 0;
    size_t read_items;
    
    while(!feof(f))
    {
        read_items = fread(buffer, sizeof(char), 100, f);
        read_total += read_items;
        
        for(size_t i = 0; i < read_items; i++)
        {
            if(isprint(buffer[i]))
            {
                printf("%c",buffer[i]);
            }
            else
                printf("?");
        }
    }
    fclose(f);
    return read_total;
}


/* Prints the given file as hexdump, at most 16 numbers per line.
 * <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int hexdump(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if(!f)
        return -1;
    
    char buffer[16];
    int read_total = 0;
    size_t read_items;
    
    while(!feof(f))
    {
        read_items = fread(buffer, sizeof(char), 16, f);
        read_total += read_items;
        
        for(size_t i = 0; i < read_items; i++)
        {
            printf("%02x ",buffer[i]);            
        }
        if(read_items == 16)
            printf("\n");
    }
    fclose(f);
    return read_total;
}
