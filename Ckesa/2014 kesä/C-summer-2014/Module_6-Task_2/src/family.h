#ifndef AALTO_FAMILY_H
#define AALTO_FAMILY_H

struct person {
        char name[15];
        struct person *father;
        struct person *mother;
        unsigned int nChildren; // length of the children array
        struct person **children;  // dynamic array of children
};

struct person *newPerson(const char *name,
                         struct person *dad, struct person *mom);

int removePerson(struct person *p);

int removeDescendants(struct person *p);

#endif
