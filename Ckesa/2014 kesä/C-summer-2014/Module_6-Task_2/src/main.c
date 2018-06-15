#include <stdio.h>
#include "family.h"


int main(void)
{
    // Inventing a weird family tree to test Exercise 6.2
    // feel free to modify
    struct person *p1 = newPerson("Kantaemo", NULL, NULL);
    //struct person *p2 = newPerson("Kantaisa", NULL, NULL);
    struct person *p3 = newPerson("Kartturi-Artturi", p1, NULL);
    //struct person *p4 = newPerson("Bertta", p1, NULL);
    //struct person *p5 = newPerson("Celina", p1, p2);
    //struct person *p6 = newPerson("Lapsi", p3, p4);
    //newPerson("Lapsi-2", p6, p5);

    //removePerson(p3);  /* uncomment to test single removal */

    printf("remove 1: %d\n", removeDescendants(p1));
    //printf("remove 2: %d\n", removeDescendants(p2));
}
