#include <stdio.h>
#include <math.h>
#include "source.h"

/* Exercise 1.1 */
void three_lines(void)
{
    printf("June\nJuly\nAugust\n");
}


/* Calculates value^2 */
double powertwo(double value)
{
    return pow(value, 2);
}

/* Calculates distance between two points */
double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/* Exercise 1.2: Calculates distance from (0,0) */
double distOrigo(double x, double y)
{
    double d;
    d = distance(x, y, 0, 0);
    return d;
}


/* Exercise 1.3 */
void simple_sum(void)
{
    int ret,a,b,sum;
    ret = scanf("%d %d",&a,&b);
    sum = a + b;
    printf("%d + %d = %d\n",a,b,sum);
}


/* Exercise 1.4 */
float simple_math(void)
{
    float eka, toka;
    unsigned char op;
    scanf("%f %c %f",&eka, &op, &toka);
    if(op == '+')
        return eka + toka;
    else if(op == '-')
        return eka - toka;
    else if(op == '*')
        return eka * toka;
    else if(op == '/')
        return eka / toka;
    else
        return 0.0 / 0.0;
}
