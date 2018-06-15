#include <stdio.h>
#include "anydata.h"


/* 01_anydata (a)
 * Return a new AnyData object based on the given input
 */
AnyData setDouble(double value)
{
	AnyData joku;
	joku.type = DOUBLE;
	joku.value.dval = value;
	return joku;

}

AnyData setInt(int value)
{ival
	AnyData joku;
	joku.type = INT;
	joku.value.ival = value;
	return joku;
}

AnyData setString(char* value)
{
	AnyData joku;
	joku.type = STRING;
	joku.value.sval = value;
	return joku;
}


void printDouble(double val)
{
    printf("D:%lf", val);
}

void printInt(int val)
{
    printf("I:%d", val);
}

void printString(char* val)
{
    printf("S:%s", val);
}

/* 01_anydata (b)
 * Print the given AnyData value, using one of the above functions
 */
void printValue(AnyData val)
{
	switch(val.type){
		case UNDEF:
			break;
		case INT:
			printInt(val);
			break;
		case DOUBLE:
			printDouble(val);
			break;
		case STRING:
			printString(val);
			break;
		
	}
}















