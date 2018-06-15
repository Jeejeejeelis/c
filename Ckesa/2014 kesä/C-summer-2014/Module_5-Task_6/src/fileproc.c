#include "fileproc.h"
#include <stdio.h>
#include <stdlib.h>


/* Process file <srcfile> using processing function <proc>, and output
 * the result to file <dstfile>. The file should be read, processed and
 * written in units of <unitsize> bytes.
 * 
 * The <proc> function has three parameters: first parameter is pointer to
 * the buffer that contains a chunk to be processed (with at most unitsize
 * bytes). The second parameter is optional parameter, that is passed to
 * process_file function as <param>. The last parameter is the length of the
 * buffer, typically same as <unitsize>, but possibly less, if less data
 * was read from file.
 * 
 * The function returns number of bytes processed, or -1 if there was failure.
 * 
 * The <proc> function returns 1 if processing was successful and should continue
 * or 0, if the processing should stop. In this case the process_file function
 * ends right away, and returns the number of bytes processed.
 */
int process_file(const char *dstfile, const char *srcfile,
        int (*proc)(char *, void *, unsigned int),
        void *param, unsigned int unitsize)
{
    FILE* dst = fopen(dstfile, "w");
    FILE* src = fopen(srcfile, "r");
    if(!dst || !src)
        return -1;
    
    size_t read;
    size_t total_read = 0;
    char* buff = malloc(unitsize);
    
    while(!feof(src))
    {
        read = fread(buff, 1, unitsize, src);
        total_read += read;
        if(!proc(buff, param, read))
            return total_read;
        fwrite(buff, 1, read, dst);
    }
    fclose(src);
    fclose(dst);
    free(buff);
    return total_read;
}


/* One processing function that can be used together with the above function.
 * This function should apply byte-by-byte XOR operation on buffer <buf> that
 * has length of <size> bytes. <key> contains the key, i.e. the values that
 * should be XOR'ed to data. The first byte of data is applied with first byte
 * of key, the second byte of data with second byte of key, and so on.
 * 
 * The function always returns 1.
 */
int xorcrypt(char *buf, void *key, unsigned int size)
{
  /*(void) buf;
  (void) key;
  (void) size;
    return 0;*/
    char* k = key;
    for(size_t i = 0; i < size; i++)
    {
        buf[i] = buf[i] ^ k[i];
    }
    return 1;
}
