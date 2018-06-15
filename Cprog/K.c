#include <stdio.h>
#include <string.h>

int main(void)
{
    char buffer[40];
    char *strings[] = { "Paasikivi", "Kekkonen", "Koivisto",
                        "Ahtisaari", "Halonen" };
    int left, i;

    strcpy(buffer, "");
    left = sizeof(buffer);
    i = 0;
    while (left > 0 && i < 5) {
        char *nimi = strings[i];
        if (*nimi == 'K'){
            strncat(buffer, strings[i], left - 1);
        }
        
        left = left - strlen(strings[i]);
        i++;
    }
    printf("buffer: %s, length: %lu\n", buffer, strlen(buffer));
}