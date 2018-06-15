#include <stdio.h>
#include "anydata.h"


/* Exercise 4.1.a functions
 * Return a new AnyData object based on the given input
 */
AnyData setDouble(double value)
{
    AnyData ad;
    ad.type = DOUBLE;
    ad.value.dval = value;
    return ad;
}

AnyData setInt(int value)
{
    AnyData ad;
    ad.type = INT;
    ad.value.ival = value;
    return ad;
}

AnyData setByte(char value)
{
    AnyData ad;
    ad.type = BYTE;
    ad.value.bval = value;
    return ad;
}


void printDouble(double val)
{
    printf("D:%lf", val);
}

void printInt(int val)
{
    printf("I:%d", val);
}

void printByte(char val)
{
    printf("B:%d", val);
}

/* Exercise 4.1.b:
 * Print the given AnyData value, using one of the above functions
 */
void printValue(AnyData val)
{
    switch(val.type)
    {
        case UNDEF:
            break;
        case INT:
            printInt(val.value.ival);
            break;
        case DOUBLE:
            printDouble(val.value.dval);
            break;
        case BYTE:
            printByte(val.value.bval);
            break;
            
    }
}



/* Exercise 4.1.c:
 * calculate sum between array of AnyData objects.
 * first points to the first member of the array
 * last points to the last member of the array
 * 
 * Returns the sum as AnyData object. Must be as "small" data type as possible.
 */
AnyData calcSum(AnyData *first, AnyData *last)
{
    AnyData ad;
    ad.type = BYTE;
    ad.value.bval = 0;
    int i = 0;
    do 
    {
        switch(ad.type) 
        {
            case UNDEF:
                break;
            case BYTE:
                switch(first[i].type)
                {
                    case UNDEF:
                        break;
                    case BYTE:
                        ad.value.bval += first[i].value.bval;
                        break;
                    case INT:
                        ad.type = INT;
                        ad.value.ival = ad.value.bval + first[i].value.ival;
                        break;
                    case DOUBLE:
                        ad.type = DOUBLE;
                        ad.value.dval = ad.value.bval + first[i].value.dval;
                        break;
                }
                break;
                    
            case INT:
                switch(first[i].type)
                {
                    case UNDEF:
                        break;
                    case BYTE:
                        ad.value.ival = ad.value.ival + first[i].value.bval;
                        break;
                    case INT:
                        ad.value.ival += first[i].value.ival;
                        break;
                    case DOUBLE:
                        ad.type = DOUBLE;
                        ad.value.dval = ad.value.ival + first[i].value.dval;
                        break;
                }
                break;
                
            case DOUBLE:
                switch(first[i].type)
                {
                    case UNDEF:
                        break;
                    case BYTE:
                        ad.value.dval = ad.value.dval + first[i].value.bval;
                        break;
                    case INT:
                        ad.value.dval = ad.value.dval + first[i].value.ival;
                        break;
                    case DOUBLE:
                        ad.value.dval += first[i].value.dval;
                        break;
                }
                break;
        }
        i++;
    } while(first + i != last + 1);
    
    return ad;
}

int main()
{
    /* Feel free to modify this function to test different things */
    /* For example, you can temporarily hide unimplemented functions
     * inside comments */

    AnyData array[5];
    
    array[0] = setDouble(3.14159);
    array[1] = setByte(2);
    array[2] = setByte(3);
    array[3] = setInt(10000);
    array[4] = setDouble(5.555);
    
    for (int i = 0; i < 5; i++) {
        printValue(array[i]);
        printf("\n");
    }
    
    printValue(calcSum(&array[1], &array[3]));
}
