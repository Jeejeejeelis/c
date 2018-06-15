#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"


void print_product(struct product *p)
{
    printf("%s (%s) -- stock: %d, price: %lf\n",
                p->title, p->code,
                p->stock, p->price);
}

int main()
{
    /* testing exercise 3.5. Feel free to modify this function */

    struct product *list = NULL;
    
    list = add_product(NULL, "test", "1234", 1, 0.50);
    add_product(list, "Product 1", "0000", 0, 10);
    add_product(list, "Long name, isn't it", "1234567890", 10, 100);
    add_product(list, "Product 3", "9999999", 0, 20);    

    struct product *p = find_product(list, "0000");
    if (p)
        print_product(p);
    else
        printf("Not found\n");

    list = remove_product(list, "0000");

    delete_list(list);
}
