#include <stdio.h>
#include <stdint.h>
#include "crypt.h"


int main(void)
{
    //const uint32_t key = 0x00000000;
    const uint32_t key = 0x63de2a3e;
    encrypt("main.c.enc", "main.c", key);
    
    if (encrypt("main.c.enc", "main.c", key) == -1) {
        if (encrypt("main.c.enc", "src/main.c", key) == -1) {
            fprintf(stderr, "Could not open main.c\n");
        }
    }
    
    if (decrypt("main.c.2", "main.c.enc", key) == -1) {
        fprintf(stderr, "decrypt failed\n");
    }
}
