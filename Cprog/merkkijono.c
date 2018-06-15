
#include <stdio.h>
#include <string.h>
int count_substr(const char *str, const char *sub)
{
	int sub_pituus = strlen(sub);
	int maara = 0;

	const char *uusi = str;

	if (sub_pituus) 
    while ((uusi = strstr(uusi, sub))) {
        uusi += sub_pituus;
        maara++;
    }
    return maara;
}

