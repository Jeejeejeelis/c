#include <stdio.h>
#include <math.h>
#include <ctype.h>

int count_alpha(const char *str)
{
	int i = 0;
    while (*str) {  // Lopettaa kun tullaan \0 - merkkiin
    	int a = isalpha(*str);
		
		if (a == 0)
		{
			NULL;
		} else {
			i = i+1;

		}
        str++;  // siirry seuraavan merkin kohdalle
    }
    return i;
}
