#include "source.h"
#include <stddef.h>
#include <stdlib.h>


/* Exercise 3.1: Dynamic Array Reader */
/* Parameters:
 * n: Number of values to be read
 * 
 * Returns: pointer to the dynamically allocated array
 */
int *dyn_reader(unsigned int n)
{
    int rtrn = 0;
    int* vals = malloc(n * sizeof(int));
    if(vals == NULL)
        return NULL;
    int i;
    for(i = 0; i < n; i++)
    {
        scanf("%d", vals + i);
    }
    return vals;
}

/* Exercise 3.2: Add to array */
/* Parameters:
 * arr: Existing array of integers
 * num: number of integers in the array before the call
 * newval: new value to be added
 * 
 * Returns: pointer to the allocated array
 */
int *add_to_array(int *arr, unsigned int num, int newval)
{
    int* newArr = realloc(arr,(num + 1) * sizeof(int));
    newArr[num] = newval;
    return newArr;
}
