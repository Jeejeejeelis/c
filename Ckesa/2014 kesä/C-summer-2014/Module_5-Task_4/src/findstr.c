#include "findstr.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

/* Searches for given string inside a file, starting from given offset.
 * (fix to original solution provided by Markus Holmström)
 * 
 * Parameters:
 * str: The string to be looked for
 * filename: name of the file to be searched
 * offset: starting point for the search, in bytes
 * 
 * Parameter:
 * The offset from which the string was first found */
long find_string(const char *str, const char *filename, long offset)
{
    FILE* f = fopen(filename, "r");
    if(!f)
        return -1;
    fseek(f, offset, SEEK_SET);
    
    long rtrn = -1;
    char c;
    
    while(!feof(f))
    {
        c = fgetc(f);
        if(c == str[0])
        {
            rtrn = ftell(f) - 1;
            for(size_t i = 1; i < strlen(str); i++)
            {
                c = fgetc(f);
                if(c != str[i])
                    rtrn = -1;
            }
            if(rtrn != -1)
                return rtrn;
        }
    }
    return rtrn;
}
