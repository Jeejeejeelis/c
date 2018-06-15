#include <stdlib.h>
#include "list.h"
#include <string.h>


/* Exercise 3.5.a: Add product */
/* Parameters:
 * start: start of the linked list
 * title, code, stock, price: to be copied as created structure content
 * 
 * Returns: pointer to the newly added node in the linked list
 */
struct product *add_product(struct product *start, const char *title, const char *code,
        int stock, double price) 
{
    struct product* pr = malloc(sizeof(struct product));
    if(!pr)
        return pr;
    struct product* last;
    for(last = start; last && last->next; last = last->next);
    if(last)
       last->next = pr; 
    
    pr->next = NULL;
    
    size_t title_length = strlen(title) + 1;
    pr->title = malloc(title_length);
    strcpy(pr->title,title);
    strncpy(&(pr->code),code,7);
    (pr->code)[7] = '\0';
    pr->stock = stock;
    pr->price = price;
    
    return pr;
}

/* Exercise 3.5.b: Find product */
/* Parameters:
 * start: first element in the linked list
 * code: product code to be found
 * 
 * Returns: Pointer to the first instance of product, or NULL if not found
 */
struct product *find_product(struct product *start, const char *code) 
{
    if(!start)
        return NULL;
    
    struct product* pr;
    for(pr = start; pr && pr->next; pr = pr->next)
        if(!strcmp(pr->code, code))
            return pr;
    return NULL;
}

/* Exercise 3.5.c: Remove Product */
/* Parameters:
 * start: The first element in list
 * code: value to be removed
 * 
 * Returns: Pointer to the first element in the linked list
 */
struct product *remove_product(struct product *start, const char *code) 
{
    struct product* pr = find_product(start, code);
    if(!pr)
        return start;
    
    struct product* next = pr->next;
    
    struct product* rtrn;
    
    if(start != pr)
    {
        struct product* last;
        for(last = start; last->next != pr;last = last->next);
        last->next = next;
        rtrn = start;
    }
    else
        rtrn = next;
    
    free(pr->title);
    free(pr);
    
    return rtrn;
}

/* Exercise 3.5.d: Delete list */
/* Parameters:
 * start: first element in linked list
 * 
 * Returns: 1, when list has been deleted
 */
int delete_list(struct product *start) 
{
    while(start)
    {
        struct product* next = start->next;
        free(start->title);
        free(start);
        start = next;
    }
    return 1;
}
