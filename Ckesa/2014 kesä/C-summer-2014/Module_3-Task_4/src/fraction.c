#include "fraction.h"
#include <stddef.h>
#include <stdlib.h>

/* Algorithm for determining greatest common divisor, needed in Task 16.5 */
/* The function returns gcd between the two parameters, u and v */
/* Taken from http://en.wikipedia.org/wiki/Binary_GCD_algorithm */
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;
 
    if (u == 0)
        return v;
 
    if (v == 0)
        return u;
 
    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }
 
    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);
 
    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);
 
    return gcd((v - u) >> 1, u);
}

struct fraction_st {
    size_t numerator;
    size_t denominator;
};

/* Exercise 3.4.a: Set fraction
 * Parameters: numerator and denominator
 * Returns: pointer to allocated fraction
 */
Fraction* setFraction(unsigned int numerator, unsigned int denominator)
{
    Fraction* rtrn = malloc(sizeof(Fraction));
    rtrn->numerator = numerator;
    rtrn->denominator = denominator;
}

unsigned int getNum(const Fraction *f)
{
    return f->numerator;
}

unsigned int getDenom(const Fraction *f)
{
    return f->denominator;
}

void freeFraction(Fraction *f)
{
    free(f);
}


/* Exercise 3.4.b: Compare values
 * Parameters: two fractions to be compared
 * Returns:
 * -1 if a is smaller than b
 * 0 if the fractions are equal
 * 1 if a is larger than b
 */
int compFraction(const Fraction *a, const Fraction *b)
{
    int erotus = a->numerator * b->denominator - b->numerator * a->denominator;
    if(erotus < 0)
        return -1;
    else if(erotus == 0)
        return 0;
    else
        return 1;
}

/* Exercise 3.4.c: Add values
 * Parameters: two fractions to be added
 * Returns: sum of the fractions
 */
Fraction* addFraction(const Fraction *a, const Fraction *b)
{
    Fraction* rtrn = malloc(sizeof(Fraction));
    rtrn->numerator = a->numerator * b->denominator + 
                      b->numerator * a->denominator;
    rtrn->denominator = a->denominator * b->denominator;
    return rtrn;
}


/* Exercise 3.4.e: Reduce fraction
 * Parameters: Fraction to be reduced. Reduction happens on the object itself */
void reduceFraction(Fraction* val)
{
    size_t jakaja = gcd(val->numerator,val->denominator);
    val->numerator = val->numerator / jakaja;
    val->denominator = val->denominator / jakaja;
}

/* Not needed, but it will be useful to implement this */
void printFraction(const Fraction *val)
{
}
