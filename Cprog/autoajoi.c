#include <stdio.h>
#include <stddef.h>

void es_print(const char *s)
{
    while (*s) {  // Lopettaa kun tullaan \0 - merkkiin
        if (*s == '#'){
            break;
        }
        printf("%c", *s);
        s++;  // siirry seuraavan merkin kohdalle
    }
}

unsigned int es_length(const char *s)
{
    int i = 0;
    while (*s) {  // Lopettaa kun tullaan \0 - merkkiin
        if (*s=='#'){
            break;
        } else {
            i++;
            s++;  // siirry seuraavan merkin kohdalle
        }
        
    }
    return i;
}

int es_copy(char *dst, const char *src)
{
    char *uusi = dst;
   while (*src) {  // Lopettaa kun tullaan \0 - merkkiin
        if (*src == '#'){
            *uusi = *src;
            break;
        }
        *uusi = *src;
        uusi++;
        src++;  // siirry seuraavan merkin kohdalle
    }
    
    return es_length(dst);
}

char *es_token(char *s, char c)
{
    return NULL;

}