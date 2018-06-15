#include <stdio.h>
#include "source.h"

int main()
{
    /* Implement your own tests here. Free feel to modify. */

    char str[] = "yksi,kaksi,kymmenen#nelja,viisi";

    // Testing 2.9.a
    es_print(str);
    
    // Testing 2.9.b
    printf("\nlength: %d\n", es_length(str));
    
    // Testing 2.9.c
    char buf[80] = { 0 };
    int ret = es_copy(buf, str);
    printf("after copy: '%s'  (ret: %d)\n", buf, ret);
    
    // Testing 2.9.d
    char *strptr = str;
    do {
        strptr = es_token(strptr, ',');
    } while (strptr);
    printf("after token: '%s'\n", str);
    
#if 0
    int n = es_demo(str, ',');
    if (n == 3)
        printf("Success!");
    else
        printf("Fail...");
#endif
    
    return 0;
}
