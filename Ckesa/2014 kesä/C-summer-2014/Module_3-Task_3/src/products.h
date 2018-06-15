#ifndef AALTO_CSUM14_33
#define AALTO_CSUM14_33

// Single product in inventory
struct product {
    char *title;  // Name of the product
    char code[8]; // Max. 7 characters of product ID
    int stock;  // Current stock (number of units)
    double price;  // Price of a single unit
};

struct product_array {
    struct product *arr;
    unsigned int count;
};

void init_product(struct product *pr, const char *title, const char *code,
        int stock, double price);
void add_product(struct product_array *pa, const char *title, const char *code,
        int stock, double price);
int remove_all(struct product_array *pa);
struct product *find_product(struct product_array *pa, const char *code);
void delete_product(struct product_array *pa, const char *code);

#endif
