#include <stdio.h>
#include "findstr.h"

int main()
{
    long output = find_string("kaksi", "testi.txt", 0);
    printf("find: %ld\n", output);
    
    output = find_string("kaksi", "testi.txt", output-1);
    printf("find B: %ld\n", output);
}
