#include <stdlib.h>
#include <stddef.h>
#include "fraction.h"

/* Algorithm for determining greatest common divisor, needed in (d) */
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

Fraction* setFraction(unsigned int numerator, unsigned int denominator){
    
    Fraction* rtr = malloc(sizeof(Fraction));
    rtr->numerator = numerator;
    rtr->denominator = denominator;

}

void freeFraction(Fraction *f){
    
    free(f);
}

unsigned int getNum(const Fraction *f){
    
    return f->numerator;
}

unsigned int getDenom(const Fraction *f){
    
    return f->denominator;
}

int compFraction(const Fraction *a, const Fraction *b){

    int a_ristiin = (a->numerator) * (b->denominator);
    int b_ristiin = (b->numerator) * (a->denominator);
    
    int subtraction = a_ristiin - b_ristiin; // Ristiinkerro -> erotus kertoo onko a pienempi tai isompi!
    
    if(subtraction < 0)
        return -1;

    else if(subtraction == 0)
        return 0;

    else
        return 1;

}

Fraction* addFraction(const Fraction *a, const Fraction *b){

    Fraction* rtr = malloc(sizeof(Fraction));
    //a ja b ristiin. alla osoittajat.
    int a_ristiin = a->numerator * b->denominator;
    int b_ristiin = b->numerator * a->denominator;
    //nimittaja ristiin alla.
    int nimittaja_ristiin =  a->denominator * b->denominator;

    rtr->numerator = a_ristiin + b_ristiin;
    rtr->denominator = nimittaja_ristiin;
    return rtr;
}

void reduceFraction(Fraction* val){

    size_t jakaja = gcd(val->numerator,val->denominator);
    
    val->numerator = val->numerator / jakaja;
    val->denominator = val->denominator / jakaja;
}

void printFraction(const Fraction *val)
{
}



