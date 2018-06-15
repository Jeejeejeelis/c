#include "stringman.h"
#include "string.h"
#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"
#include <math.h>

/* Exercise 6.1.a: reverse the string pointed by parameter <p>.
 * The string is modified in place: after function exits, <p> contains
 * the reversed string.
 */
void turn_around(char *p)
{
    char nstr[strlen(p) + 1];
    for(size_t i = 0; i <= strlen(p); i++)
    {
        nstr[i] = p[strlen(p) - 1 - i];
    }
    nstr[strlen(p)] = '\0';
    strcpy(p, nstr);
}

/* Exercise 6.1.b: Returns 1 if given string is palindrome, 0 if it is not
 */
int is_reversed(const char *p)
{
    size_t size = strlen(p);
    for(size_t i = 0; i < size / 2; i++)
    {
        if(p[i] != p[size - 1 - i])
            return 0;
    }
    return 1;
}


/* Exercise 6.1.c: Reverse all words in given string <p>. "Word" consists of
 * alphanumeric characters, and any non-alphanumeric character splits the
 * word.
 */
void reverse_word(char* wStart, size_t wSize)
{
    char nstr[wSize];
    for(size_t i = 0; i < wSize; i++)
    {
        nstr[i] = wStart[wSize - 1 - i];
    }
    strncpy(wStart, nstr, wSize);
}

void reversed_words(char *p)
{
    size_t size = strlen(p);
    size_t wSize = 0;
    size_t wStartI = 0;
    for(size_t i = 0; i <= size; i++)
    {
        if(!isalnum(p[i]) || i == size)
        {
            wSize = i - wStartI;
            reverse_word(p + wStartI, wSize);
            wStartI = i + 1;
        }
    }
}
/*
 * 
 * abc abc
 * 01234567
 * 
 * 
 
 */
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

int count_words(const char* wStart, int wSize, const char* p)
{
    int count = 0;
    size_t size = strlen(p);
    const char* start = p;
    for(size_t i = 0; i <= size; i++)
    {
        if(i == size || !isalnum(p[i]))
        {
            char cond = 0;
            for(int j = 0; j < wSize; j++)
            {
                if(wStart[j] != start[j])
                {
                    cond = 0;
                    break;
                }
                else
                    cond = 1;
            }
            if(cond)
            {
                count++;
            }
            start = p + i + 1;
        }
    }
    return count;
}


/* Exercise 6.1.d: return the most common word in given string <p>. That word
 * is written to the buffer pointed by <result>. Size of the <result> buffer is
 * indicated in <size>. "Word" consists of alphanumeric characters, and any
 * non-alphanumeric character ends the word.
 * 
 * Returns: number of times the most common word was present in the string
 */

int most_common(const char *p, char *result, int size)
{
    size_t pSize = strlen(p);
    char mc[size];
    int mCCount = 0;
    int count = 0;
    const char* wStart = p;
    int wSize;
    for(size_t i = 0; i <= pSize; i++)
    {
        if(i == pSize || !isalnum(p[i]))
        {
            wSize = p + i - wStart;
            count = count_words(wStart, wSize, p);
            if(count > mCCount)
            {
                strncpy(mc, wStart, MIN(wSize, size - 1));
                mc[MIN(wSize, size - 1)] = '\0';
                mCCount = count;
            }
            wStart = p + i + 1;
        }
    }
    strncpy(result, mc, size);
    return mCCount;
}


