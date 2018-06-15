#include <stdio.h>
#include "fileproc.h"

int main(void)
{
    /* Here is an example of using the process_file function together
     with xorcrypt processing function. */
    unsigned char key[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
    int ret = process_file("testi.enc", "testi.txt", xorcrypt, key, 8);
    printf("process_file returned %d. See testi.enc for the results of processing", ret);
}
