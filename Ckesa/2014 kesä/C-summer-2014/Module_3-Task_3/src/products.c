#include <stdlib.h>
#include "products.h"
#include <string.h>


/* Exercise 3.3.a: Initialize product structure */
/* Parameters:
 * pr: Pointer to single product structure
 * title, code, stock, price: values to be copied as structure content.
 * Note: code should be truncated to 7 characters, if it is longer
 */
void init_product(struct product *pr, const char *title, const char *code,
        int stock, double price)
{
    size_t title_length = strlen(title) + 1;
    pr->title = malloc(title_length);
    strcpy(pr->title,title);
    strncpy(&(pr->code),code,7);
    (pr->code)[7] = '\0';
    pr->stock = stock;
    pr->price = price;
}

/* Exercise 3.3.b: Add product to array */
/* Parameters:
 * pa: Product array to where a new item is added
 * title, code, stock, price: values to be copied as structure content.
 * Note: code should be truncated to 7 characters, if it is longer
 */
void add_product(struct product_array *pa, const char *title, const char *code,
        int stock, double price)
{
    pa->arr = realloc(pa->arr, (++(pa->count)) * sizeof(struct product));
    init_product((pa->arr) + (pa->count) - 1, title, code, stock, price);
}


/* Exercise 3.3.c: Remove all array elements */
/* Parameters:
 * pa: Product array to be removed
 *       
 * Returns: 1 when the function is properly implemented
 */
int remove_all(struct product_array *pa)
{
    int i;
    for(i = 0; i < pa->count; i++)
    {
        free(((pa->arr) + i)->title);
    }
    free(pa->arr);
    return 1;
}


/* Exercise 3.3.d: Find product */
/* Parameters:
 * pa: Product array structure
 * code: product code that will be searched for
 *       
 * Returns: pointer to the matching product in array, NULL if not found
 */
struct product *find_product(struct product_array *pa, const char *code) {
    int i;
    for(i = 0; i < pa->count; i++)
    {
        if(!strcmp((pa->arr + i)->code,code))
            return pa->arr + i;
    }
    return NULL;
}


/* Exercise 3.3.e: Delete product */
/* Parameters:
 * pa: Product array structure
 * code: product code that will be deleted
 */
void delete_product(struct product_array *pa, const char *code) 
{
    struct product* poistettava = find_product(pa, code);
    if(!poistettava)
        return;
    
    free(poistettava->title);
    
    size_t indeksi = poistettava - pa->arr;
    size_t viimeinen_indeksi = pa->count - 1;
    size_t siirrettava = (viimeinen_indeksi - indeksi) * sizeof(struct product);
    if(siirrettava)
        memmove(poistettava, poistettava + 1, siirrettava);
    
    pa->arr = realloc(pa->arr,viimeinen_indeksi * sizeof(struct product));
    pa->count--;
}
