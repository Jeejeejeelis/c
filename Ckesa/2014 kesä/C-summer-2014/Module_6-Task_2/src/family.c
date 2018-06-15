#include "family.h"
#include "stdio.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"



/* Exercise 6.2.a: Create a new person with given name, given father and
 * given mother. <dad> and <mom> can also be NULL.
 * Returns pointer to the newly allocated person.
 */
struct person *newPerson(const char *name,
                         struct person *dad, struct person *mom)
{
    struct person* ptr = malloc(sizeof(struct person));
    strncpy(ptr->name, name, 14);
    ptr->name[14] = '\0';
    ptr->father = dad;
    ptr->mother = mom;
    ptr->nChildren = 0;
    ptr->children = NULL;
    if(dad)
    {
        dad->children = realloc(dad->children, (dad->nChildren + 1) * sizeof(struct person*));
        dad->children[dad->nChildren] = ptr;
        dad->nChildren++;
    }
    if(mom)
    {
        mom->children = realloc(mom->children, (mom->nChildren + 1) * sizeof(struct person*));
        mom->children[mom->nChildren] = ptr;
        mom->nChildren++;
    }
    return ptr;
}


/* Exercise 6.2.b: Remove given person and release the allocated memory.
 * Remember to remove also any possible references to this person from
 * the parents.
 * Returns number of persons removed, i.e., 1 if everything went ok
 */
int removePerson(struct person *p)
{
    if(p->father)
    {
        for(size_t i = 0; i < p->father->nChildren; i++)
        {
            if(p->father->children[i] == p)
                p->father->children[i] = NULL;
        }
    }
    if(p->mother)
    {
        for(size_t i = 0; i < p->mother->nChildren; i++)
        {
            if(p->mother->children[i] == p)
                p->mother->children[i] = NULL;
        }
    }
    free(p->children);
    free(p);
    return 1;
}

/* Exercise 6.2.c: Remove the given person and all his/her descendants.
 * Returns the number of persons removed.
 */
int removeDescendants(struct person *p)
{
    int dCount = 0;
    for(size_t i = 0; i < p->nChildren; i++)
    {
        if(p->children[i])
            dCount += removeDescendants(p->children[i]);
    }
    dCount += removePerson(p);
    return dCount;
}
