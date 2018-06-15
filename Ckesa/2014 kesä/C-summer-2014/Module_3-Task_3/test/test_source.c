#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../src/products.h"


void see_remove_all(struct product_array *pa)
{
    if (remove_all(pa))
        return;
    
}


int test_product(char *buf, struct product *pr, const char *title, const char *code,
        int stock, double price) {
    if (pr->title == title || pr->title == NULL) {
        sprintf(buf, "Memory for title string not dynamically allocated");
        return 0;
    }
    if (strcmp(pr->title, title)) {
        remove_nonascii(pr->title);
        sprintf(buf, "Incorrect title. You: \"%s\", expected: \"%s\"",
                pr->title, title);
        return 0;
    }

    if (strlen(pr->code) > 7) {
        sprintf(buf, "Code field is too long. Max. length is 7 characters (plus '\\0')");
        return 0;
    }
    char codebuf[8];
    strncpy(codebuf, code, 7);
    codebuf[7] = 0;

    if (strcmp(pr->code, codebuf)) {
        remove_nonascii(pr->code);
        sprintf(buf, "Incorrect code. You: \"%s\", expected: \"%s\"",
                pr->code, codebuf);
        return 0;
    }
    if (pr->stock != stock) {
        sprintf(buf, "Incorrect stock. You: %d, expected: %d",
                pr->stock, stock);
        return 0;
    }
    if (pr->price != price) {
        sprintf(buf, "Incorrect price. You: %lf, expected: %lf",
                pr->price, price);
        return 0;
    }
    return 1;
}

START_TEST(test_init_product) {
    char *titles[] = {"Floppy disk", "USB stick", "Something with quite long name", "Laptop"};
    char *codes[] = {"0000", "1234567890", "4444444", "1111"};
    int stocks[] = {1, 2, 3, 4};
    double prices[] = {0.1, 1, 10, 100};

    for (unsigned int i = 0; i < 4; i++) {
        struct product p;
        p.title = NULL;
        init_product(&p, titles[i], codes[i], stocks[i], prices[i]);
        char buf[200];
        buf[0] = 0;
        int ret = test_product(buf, &p, titles[i], codes[i], stocks[i], prices[i]);
        if (!ret) {
            if (p.title && p.title != titles[i])
                free(p.title);
            fail("[Task 3.3.a] Struct not initialized properly: %s", buf);
        }
	free(p.title);
    }
}

END_TEST


START_TEST(test_add_product) {
    char *titles[] = {"Floppy disk", "USB stick", "Something with quite long name", "Laptop"};
    char *codes[] = {"0000", "1234567890", "4444444", "1111"};
    int stocks[] = {1, 2, 3, 4};
    double prices[] = {0.1, 1, 10, 100};

    struct product_array pa;
    pa.arr = NULL;
    pa.count = 0;

    for (unsigned int i = 0; i < 4; i++) {
        add_product(&pa, titles[i], codes[i], stocks[i], prices[i]);
    }

    if (pa.count != 4) {
      see_remove_all(&pa);
      fail("[Task 3.3.b] After adding 4 items, count should be 4. You have %d",
	   pa.count);
    }

    for (unsigned int i = 0; i < 4; i++) {
        char buf[200];
        buf[0] = 0;
        int ret = test_product(buf, pa.arr + i, titles[i], codes[i], stocks[i], prices[i]);
        if (!ret) {
            see_remove_all(&pa);
            fail("[Task 3.3.b] Array element nr. %d not initialized properly: %s",
                    i + 1, buf);
        }
    }
    see_remove_all(&pa);
}
END_TEST


START_TEST(test_remove_all)
{
    char *titles[] = {"Floppy disk", "USB stick", "Something with quite long name", "Laptop"};
    char *codes[] = {"0000", "1234567890", "4444444", "1111"};
    int stocks[] = {1, 2, 3, 4};
    double prices[] = {0.1, 1, 10, 100};

    struct product_array pa;
    pa.arr = NULL;
    pa.count = 0;

    for (unsigned int i = 0; i < 4; i++) {
        add_product(&pa, titles[i], codes[i], stocks[i], prices[i]);
    }

    if (remove_all(&pa) != 1) {
        see_remove_all(&pa);
        fail("[Task 3.3.c] remove_all should return 1");
    }
}
END_TEST


START_TEST(test_find_product) {
    char *titles[] = {"Floppy disk", "USB stick", "Something with quite long name", "Laptop"};
    char *codes[] = {"0000", "1234567", "4444444", "1111"};
    int stocks[] = {1, 2, 3, 4};
    double prices[] = {0.1, 1, 10, 100};

    struct product_array pa;
    pa.arr = NULL;
    pa.count = 0;

    for (unsigned int i = 0; i < 4; i++) {
        add_product(&pa, titles[i], codes[i], stocks[i], prices[i]);
    }
    
    for (unsigned int i = 0; i < 4; i++) {
        char codebuf[8];
        strncpy(codebuf, codes[i], 7);
        codebuf[7] = 0;
        struct product *p = find_product(&pa, codebuf);
	if (!p) {
	  see_remove_all(&pa);
	  fail("[Task 3.3.d] find_product returned NULL for code '%s' that should have existed",
	       codebuf);
	}

        char buf[200];
        buf[0] = 0;
        int ret = test_product(buf, p, titles[i], codes[i], stocks[i], prices[i]);
        if (!ret) {
            see_remove_all(&pa);
            fail("[Task 3.3.d] Array element with id '%s' has invalid content: %s",
                    codebuf, buf);
        }        
    }
    
    char ne[6];
    for (int i = 0; i < 5; i++) {
        ne[i] = rand() % 20 + 'A';
    }
    ne[5] = 0;
    
    struct product *p = find_product(&pa, ne);
    if (p) {
        see_remove_all(&pa);
        fail("[Task 3.3.d] find_product should return NULL for unexisting code '%s'",
                ne);
    }
    see_remove_all(&pa);
}
END_TEST


START_TEST(test_delete_product) {
    char *titles[] = {"Floppy disk", "USB stick", "Something with quite long name", "Laptop"};
    char *codes[] = {"0000", "1234567890", "4444444", "1111"};
    int stocks[] = {1, 2, 3, 4};
    double prices[] = {0.1, 1, 10, 100};

    struct product_array pa;
    pa.arr = NULL;
    pa.count = 0;

    for (unsigned int i = 0; i < 4; i++) {
        add_product(&pa, titles[i], codes[i], stocks[i], prices[i]);
    }
    
    delete_product(&pa, codes[2]);
    struct product *p = find_product(&pa, codes[2]);
    if (p) {
        see_remove_all(&pa);
        fail("[Task 3.3.e] find_product should return NULL for just deleted code '%s'",
                codes[2]);
    }
    if (strcmp(pa.arr[2].code, codes[3])) {
        see_remove_all(&pa);
        fail("[Task 3.3.e] After deleting '%s', array element with code '%s' is not shifted appropriately",
                codes[2], codes[3]);
    }
    
    delete_product(&pa, codes[0]);
    p = find_product(&pa, codes[0]);
    if (p) {
        see_remove_all(&pa);
        fail("[Task 3.3.e] find_product should return NULL for just deleted code '%s'",
                codes[0]);
    }
    if (strcmp(pa.arr[1].code, codes[3])) {
        see_remove_all(&pa);
        fail("[Task 3.3.e] After deleting '%s', remaining array elements are not shifted appropriately",
                codes[0]);
    }
    
    p = find_product(&pa, codes[3]);
    if (p->stock != 4) {
        see_remove_all(&pa);
        fail("[Task 3.3.e] After deleting two products, code '%s' is not properly stored in array",
                codes[3]);
    }
    see_remove_all(&pa);
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-3.3");

    tmc_register_test(s, test_init_product, "3.3.a");
    tmc_register_test(s, test_add_product, "3.3.b");
    tmc_register_test(s, test_remove_all, "3.3.c");    
    tmc_register_test(s, test_find_product, "3.3.d");
    tmc_register_test(s, test_delete_product, "3.3.e");
    
    return tmc_run_tests(argc, argv, s);
}
