#include <stdint.h>
#include "crypt.h"
#include <stdio.h>
#include <stddef.h>

/* Encrypts file named <srcfile> and writes the encrypted file to <dstfile>.
 * Encryption is based on XOR operation using 32-bit <key>.
 * Returns number of bytes processed.
 */
int encrypt(const char *dstfile, const char *srcfile, uint32_t key)
{
    FILE* dst = fopen(dstfile, "w");
    FILE* src = fopen(srcfile, "r");
    if(!dst || !src)
        return -1;

    size_t read;
    size_t total_read = 0;
    char tavut[100];
    
    char key3 = key >> 24;
    char key2 = key >> 16;
    char key1 = key >> 8;
    char key0 = key;

    while(!feof(src))
    {
        read = fread(tavut, 1, 100, src);
        total_read += read;
        for(size_t i = 0; i < read; i++)
        {
            size_t j = i % 4;
            
            if(j == 0)
                tavut[i] = tavut[i] ^ key0;
            if(j == 1)
                tavut[i] = tavut[i] ^ key1;
            if(j == 2)
                tavut[i] = tavut[i] ^ key2;
            if(j == 3)
                tavut[i] = tavut[i] ^ key3;
        }
        fwrite(tavut, 1, read, dst);
    }
    fclose(src);
    fclose(dst);
    return total_read;
}

/* Decrypts file named <srcfile> and writes the decrypted file to <dstfile>.
 * Decryption is based on XOR operation using 32-bit <key>.
 * Returns number of bytes processed.
 */
int decrypt(const char *dstfile, const char *srcfile, uint32_t key)
{
    FILE* dst = fopen(dstfile, "w");
    FILE* src = fopen(srcfile, "r");
    if(!dst || !src)
        return -1;

    size_t read;
    size_t total_read = 0;
    char tavut[100];
    
    char key3 = key >> 24;
    char key2 = key >> 16;
    char key1 = key >> 8;
    char key0 = key;

    while(!feof(src))
    {
        read = fread(tavut, 1, 100, src);
        total_read += read;
        for(size_t i = 0; i < read; i++)
        {
            size_t j = i % 4;
            
            if(j == 0)
                tavut[i] = tavut[i] ^ key0;
            if(j == 1)
                tavut[i] = tavut[i] ^ key1;
            if(j == 2)
                tavut[i] = tavut[i] ^ key2;
            if(j == 3)
                tavut[i] = tavut[i] ^ key3;
        }
        fwrite(tavut, 1, read, dst);
    }
    fclose(src);
    fclose(dst);
    return total_read;
}
