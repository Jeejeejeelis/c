#include <stdio.h>
#include <string.h>
#include "hexread.h"


int dump_hex(const char *filename){

	FILE* f = fopen(filename, "r");
    if(!f){
        return -1;
    }
    
    char buff[16];
    int read_total = 0;
    size_t read_items;
    
    while(!feof(f))
    {
        read_items = fread(buff, sizeof(char), 16, f);
        read_total += read_items;
        
        for(size_t i = 0; i < read_items; i++)
        {
            printf("%02x ",buff[i]);            
        }
        if(read_items == 16)
            printf("\n");
    }
    fclose(f);
    return read_total;

}

int main(void)
{
    if (dump_hex("main.c") == -1) {
         fprintf(stderr, "Could not open main.c\n");
    }
}
