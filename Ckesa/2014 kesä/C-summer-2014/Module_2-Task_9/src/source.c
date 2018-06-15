#include "source.h"
#include <stddef.h>


/* Exercise 2.9.a: Print string */
/* Parameters:
 * s: string to be printed */
void es_print(const char *s)
{
    for(int i = 0; s[i] != '#'; i++)
    {
        printf("%c",s[i]);
    }
}

/* Exercise 2.9.b: String length */
/* Parameters:
 * s: string to be evaluated
 * Returns: length of the string */
unsigned int es_length(const char *s)
{
    int i = 0;
    for(i = 0; s[i] != '#'; i++)
    {}
    return i;
}

/* Exercise 2.9.c: String copy */
/* Parameters:
 * dst: buffer to which the new string is copied
 * src: original string
 * Returns: Number of characters copied
 */
int es_copy(char *dst, const char *src)
{
    int i;
    for(i = 0; src[i] != '#'; i++)
    {
        dst[i] = src[i];
    }
    dst[i] = '#';
    return i;
}

/* Exercise 2.9.d: String tokenizer */
/* Parameters:
 * s: string to be processed
 * c: character to be replaced by '#'
 * Returns: pointer to the character following the replaced character,
 *          NULL if end of string reached */
char *es_token(char *s, char c)
{
    int i;
    for(i = 0; s[i] != c; i++)
    {
        if(s[i] == '#')
            return NULL;
    }
    s[i] = '#';
    return s + i + 1;
}
