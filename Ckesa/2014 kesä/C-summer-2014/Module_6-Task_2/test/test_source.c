#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tmc-check.h"
#include "../src/family.h"


int checkPerson(char *out, struct person *p, const char *refname,
        struct person *refdad, struct person *refmom)
{
    unsigned long l;
    if ((l = strlen(p->name)) > 14) {
        sprintf(out, "Name too long, you have %lu characters, should be less than 15.", l);
        return 0;
    }
    if (strcmp(p->name, refname)) {
        remove_nonascii(p->name);
        sprintf(out, "Name incorrect: you have \"%s\", should be \"%s\".", p->name, refname);
        return 0;
    }
    if (p->nChildren) {
        sprintf(out, "Initially person '%s' should have 0 children.", p->name);
        return 0;
    }
    if (p->children) {
        sprintf(out, "Initially the children array for person '%s' should be set to NULL",
                p->name);
    }
    if (p->mother != refmom) {
        sprintf(out, "Person '%s' has incorrect mother.", p->name);
        return 0;
    }
    if (p->father!= refdad) {
        sprintf(out, "Person '%s' has incorrect father.", p->name);
        return 0;
    }
    return 1;
}


START_TEST(test_newPerson) {
    struct person *p1 = newPerson("Kantaemo", NULL, NULL);
    if (!p1) {
        fail("[Task 6.2.a] newPerson returned NULL");
    }
    char outbuf[200];
    outbuf[0] = 0;
    if (!checkPerson(outbuf, p1, "Kantaemo", NULL, NULL)) {
        free(p1);
        fail("[Task 6.2.a] %s", outbuf);
    }
    
    struct person *p2 = newPerson("Kantaisa", NULL, NULL);
    if (!checkPerson(outbuf, p2, "Kantaisa", NULL, NULL)) {
        free(p1);
        free(p2);
        fail("[Task 6.2.a] %s", outbuf);
    }  
    
    struct person *p3 = newPerson("Kartturi-Artturi", p1, p2);
    if (!checkPerson(outbuf, p3, "Kartturi-Arttu", p1, p2)) {
        free(p1->children); free(p1); 
        free(p2->children); free(p2); 
        free(p3);
        fail("[Task 6.2.a] %s", outbuf);
    }      
    
    struct person *p4 = newPerson("Bertta", p1, p2);
    struct person *p5 = newPerson("Lapseton", p1, p2);

    if (p1->nChildren != 3 || p2->nChildren != 3) {
        sprintf(outbuf, "[Task 6.2.a] After adding 3 children, nChildren of parents are %d and %d",
                p1->nChildren, p2->nChildren);
        free(p1->children); free(p1); 
        free(p2->children); free(p2); 
        free(p3); free(p4); free(p5);
        fail("[Task 6.2.a] %s", outbuf);       
    }
    
    struct person *refarr[] = {p3, p4, p5};
    
    for (int i = 0; i < 3; i++) {
        if (p1->children[i] != refarr[i] || p2->children[i] != refarr[i]) {
            free(p1->children); free(p1); 
            free(p2->children); free(p2); 
            free(p3); free(p4); free(p5);           
            fail("[Task 6.2.a] The array of children is not correctly set after adding 3 children.");
        }
    }
    free(p1->children); free(p1);
    free(p2->children); free(p2);
    free(p3); free(p4); free(p5);
}
END_TEST

int countChildren(struct person *p)
{
    int count = 0;
    for (unsigned int i = 0; i < p->nChildren; i++) {
        if (p->children[i])
            count++;
    }
    return count;
}

START_TEST(test_removePerson) {
    struct person *p = newPerson("Test", NULL, NULL);
    if (removePerson(p) == -1) {
        free(p);
        fail("[Task 6.2.b] removePerson returned -1");
    }
    
    struct person *p1 = newPerson("Kantaemo", NULL, NULL);
    struct person *p2 = newPerson("Kantaisa", NULL, NULL);
    struct person *p3 = newPerson("Kartturi-Artturi", p1, p2);
    struct person *p4 = newPerson("Bertta", p1, p2);
    
    int n;
    if ((n = removePerson(p3)) != 1) {
        removePerson(p4);
        removePerson(p1);
        removePerson(p2);
        fail("[Task 6.2.b] removePerson should return 1 on successful removal. You returned %d.",
                n);
    }
    
    n = countChildren(p1);
    if (n != 1) {
        removePerson(p4);
        removePerson(p1);
        removePerson(p2);
        fail("[Task 6.2.b] After adding 2 children and removing one, the parents' children array should have only one member. You have %d",
                n);
    }
    n = countChildren(p2);
    if (n != 1) {
        removePerson(p4);
        removePerson(p1);
        removePerson(p2);
        fail("[Task 6.2.b] After adding 2 children and removing one, the parents' children array should have only one member. You have %d",
                n);
    }
    
    removePerson(p4);
    n = countChildren(p1);
    if (n != 0) {
        removePerson(p1);
        removePerson(p2);
        fail("[Task 6.2.b] After adding 2 children and removing one, the parents' children array should have 0 members. You have %d",
                n);
    }
    
    removePerson(p1);
    removePerson(p2);
    p1 = NULL;  // pointers not reachable anymore
    p2 = NULL;
}
END_TEST

START_TEST(test_removeDescendants) {
    struct person *p = newPerson("Test", NULL, NULL);
    if (removeDescendants(p) == -1) {
        free(p);
        fail("[Task 6.2.c] removeDescendants returned -1");
    }    
    
    struct person *p1 = newPerson("Kantaemo", NULL, NULL);
    struct person *p2 = newPerson("Kantaisa", NULL, NULL);
    struct person *p3 = newPerson("Kartturi-Artturi", p1, p2);
    struct person *p4 = newPerson("Bertta", p1, p2);
    struct person *p5 = newPerson("Celina", p1, p2);
    struct person *p6 = newPerson("Lapsi", p3, p4);
    newPerson("Lapsi-2", p6, p5);

    int ret;
    if ((ret = removeDescendants(p1)) != 6) {
        fail("[Task 6.2.c] removeDescendants should return the number of persons removed. Expected 6, you returned %d",
                ret);
    }
    if ((ret = removeDescendants(p2)) != 1) {
        fail("[Task 6.2.c] removeDescendants should return the number of persons removed. Expected 1, you returned %d",
                ret);
    }
    p1 = NULL; p2 = NULL; p3 = NULL; p4 = NULL;  // pointers not reachable anymore
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-6.2");

    tmc_register_test(s, test_newPerson, "6.2.a");
    tmc_register_test(s, test_removePerson, "6.2.b");    
    tmc_register_test(s, test_removeDescendants, "6.2.c");
    
    return tmc_run_tests(argc, argv, s);
}
