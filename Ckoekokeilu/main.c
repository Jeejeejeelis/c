#include <stdlib.h>
#include <stdio.h>

// kirjoita funktiot tähän
char *mystrcat(char *dest, const char *src){
    size_t i,j;
    for (i = 0; dest[i] != '\0'; i++)
        ;
    for (j = 0; src[j] != '\0'; j++)
        dest[i+j] = src[j];
    dest[i+j] = '\0';
    return dest;
}
int main(void){
    char str1[] = "jee";
    char str2[] = "haa";
    char* str3 = mystrcat(str1,str2);
    printf("%s\n",str3 );
}