#ifndef AALTO_ANYDATA_H
#define	AALTO_ANYDATA_H

typedef enum {
    UNDEF,            
    INT,
    DOUBLE,
    STRING
} numType;

typedef struct {
    numType type;
    union {
        int ival;  // if INT
        double dval;  // if DOUBLE
        char sval[20]; // if string
    } value;
} AnyData;

AnyData setDouble(double value);
AnyData setInt(int value);
AnyData setString(char* value);

void printValue(AnyData val);

AnyData calcSum(AnyData *first, AnyData *second);

#endif	/* AALTO_ANYDATA_H */
