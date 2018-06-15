#include <stdio.h>
#include "source.h"


/* Exercise 2.1: Number swap
 * Swap the content of integers add addresses a and b
 */
void number_swap(int *a, int *b)
{
    int uusi_a = *b;
    int uusi_b = *a;
    *a = uusi_a;
    *b = uusi_b;
}

/* Exercise 2.2: Array Sum
 * Calculate the sum of integers in array starting at address <array>.
 * There will be <count> elements in array. Return the sum as return value.
 */
int array_sum(int *array, int count)
{
    int summa = 0;
    for(int i = 0; i < count ; i++)
    {
        summa += *(array + i);
    }
    return summa;
}

/* Exercise 2.3: Array Reader */
/* Parameters:
 * array: array to be filled 
 * size: maximum size of array
 * returns: number of values read */
int array_reader(int* vals, int n)
{
    int rtrn = 0;
    int i;
    for(i = 0; i < n; i++)
    {
        char luettuja = scanf("%d", vals + i);
        if(!luettuja)
            return rtrn;
        else
            rtrn++;
    }
}

/* Exercise 2.4: Largest number
 * Find largest integer in given array <start>. The length of the array is not
 * known in advance, but the last element has value -1. The function returns
 * the largest value in array.
 * You can assume the other array values are positive.
 */
int largest_num(int* start)
{
    int i;
    int arvo = 0;
    int suurin = 0;
    for(i = 0; arvo != -1; i++)
    {
        arvo = start[i];
        if(arvo > suurin)
            suurin = arvo;
    }
    return suurin;
    
}
