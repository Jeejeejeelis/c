#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "products.h"


void print_products(struct product_array *pa)
{
    for (unsigned int i = 0; i < pa->count; i++) {
        printf("%s (%s) -- stock: %d, price: %lf\n",
                pa->arr[i].title, pa->arr[i].code,
                pa->arr[i].stock, pa->arr[i].price);
    }
}


int main()
{
    /* testing exercise 3.3 */
    /* Feel free to modify */
    struct product_array pa;
    pa.count = 0;
    pa.arr = NULL;
    
    struct product p;
    init_product(&p, "test", "1234", 1, 0.50);
    
    add_product(&pa, "Product 1", "0000", 0, 10);
    // the below should truncate the code to 1234567
    add_product(&pa, "Long name, isn't it", "1234567890", 10, 100);
    add_product(&pa, "Product 3", "9999999", 0, 20);
    
    print_products(&pa);
    
    struct product *p1 = find_product(&pa, "1234567");
    if (p1->stock == 10) {
        // This should end up here
        printf("It worked!\n");
    }
    
    delete_product(&pa, "0000");
    
    print_products(&pa);
    
    remove_all(&pa);
}
