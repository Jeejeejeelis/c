#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strarray.h"

char **init_array(void)
{
    char** arr = malloc(sizeof(NULL));
    *arr = NULL;
    return arr;
}

void free_strings(char **array)
{
    size_t i = 0;
    char* string = array[0];
    
    while(string != NULL)
    {
        free(string);
        i++;
        string = array[i];
    }
    free(array);
}

char **add_string(char **array, const char *string)
{
    size_t i;
    for(i = 0; array[i] != NULL; i++);
    
    char** arr = realloc(array, (i + 2) * sizeof(char*));
    
    arr[i] = malloc((strlen(string) + 1) * sizeof(char));
    strcpy(arr[i], string);
    
    arr[i + 1] = NULL;
    
    return arr;
}

void make_lower(char **array)
{
    size_t imax;
    for(imax = 0; array[imax] != NULL; imax++);
    
    for(size_t i = 0; i < imax; i++)
    {
        size_t jmax = strlen(array[i]);
        for(size_t j = 0; j < jmax; j++)
        {
            array[i][j] = tolower(array[i][j]);
        }
    }
}


void sort_strings(char **array)
{
    size_t imax;
    for(imax = 0; array[imax] != NULL; imax++);
    
    for(size_t i = 0; i < imax; i++)
    {
        if(strcmp(array[0], array[i]) > 0)
        {
            char* new_first = array[i];
            array[i] = array[0];
            array[0] = new_first;
        }
    }
    
    if(imax > 1)
        sort_strings(array + 1);
}

void print_strings(char **array)
{
    if (!array)
        return;
    while (*array) {
        printf("%s  ", *array);
        array++;
    }
    printf("\n");
}


int main(void)
{
    char **strings = init_array();
    
    strings = add_string(strings, "oNe");
    strings = add_string(strings, "TWO");
    strings = add_string(strings, "three");
    strings = add_string(strings, "Four");
    
    print_strings(strings);
    
    //make_lower(strings);
    sort_strings(strings);
    
    print_strings(strings);
    free_strings(strings);
    
    return EXIT_SUCCESS;
}

