#include "source.h"
#include <ctype.h>
#include <stddef.h>
#include <string.h>


/* Exercise 2.5: Selection sort */
/* Parameters:
 * start: start of an array
 * size: length of an array
 */
void sort(int* start, int size)
{
    int eka = *start;
    int pienin = eka;
    int arvo;
    int* paikka = start;
    for(int i = 1; i < size; i++)
    {
        arvo = *(start + i);
        if(arvo < pienin)
        {
            pienin = arvo;
            paikka = start + i;
        }
    }
    *start = pienin;
    *paikka = eka;
    if(size >= 2)
        sort(start + 1, size - 1);
}



/* Exercise 2.6: Count Alpha
 * Count number of alphabetic characters in the given string <str>,
 * and return the count
 */
int count_alpha(const char* str)
{
    int count = 0;
    char* i = str;
    while(*i)
    {
        if(isalpha(*i))
            count++;
        i++;
    }
    return count;
}


/* Exercise 2.7: Count Substring
 * Count number of occurances of substring <sub> in string <str>,
 * and return the count.
 */
int count_substr(const char *str, const char *sub)
{
    int counter = 0;
    char* alku = str;
    do {
        alku = strstr(alku,sub);
        if(alku != NULL)
        {
            alku++;
            counter++;
        }
    } while(alku != NULL);
    return counter;
}


/* Exercise 2.8: Remove Alpha
 * Remove all occurances of substring <sub> from string <str>.
 * The modified string will be written in place of <str>
 */
void remove_substr(char* str, const char* sub)
{
    //Määritetään poistettavan jonon pituus.
    unsigned long pituus = strlen(sub);
    
    //Määritetään ensimmäisen merkkijonon sub alkupiste, jos sellaisia on.
    char* alku = strstr(str, sub);
    
    //Jos merkkijonoja sub ei löytynyt, ei jatketa pidemmälle.
    if(alku != NULL)
    {
        //Poistetaan jäljelle loppupäästä merkkijonot sub.
        remove_substr(alku + 1, sub);
        
        //Siirretään siivottu loppupää poistettavan osuuden päälle.
        int i;
        for(i = 0; alku[i] != '\0'; i++)
        {
            alku[i] = alku[i + pituus];
        }
        alku[i] = '\0';
    }
}