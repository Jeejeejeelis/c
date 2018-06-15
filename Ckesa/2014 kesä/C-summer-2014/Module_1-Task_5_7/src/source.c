#include <stdio.h>
#include <math.h>
#include "source.h"


/* Exercise 1.5 */
void draw_box(unsigned int xsize, unsigned int ysize)
{
    unsigned int y;
    for(y = ysize; y != 0; y--)
    {
        unsigned int x;
        for(x = xsize; x != 0; x--)
            printf("#");
        printf("\n");
    }
}


/* Exercise 1.6 */
void draw_triangle(unsigned int size)
{
    int y;
    for(y = size - 1; y >= 0; y--)
    {
        unsigned int x;
        for(x = y; x > 0; x--)
            printf(".");
        unsigned int z;
        for(z = size - y; z != 0; z--)
            printf("#");
        printf("\n");
    }
}

double distance(int x, int y)
{
    return sqrt(x * x + y * y);
}

/* Exercise 1.7 */
void draw_ball(unsigned int radius)
{
    int y;
    int r;
    r = radius;
    for(y = radius; y >= -r; y--)
    {
        int x;
        for(x = -r; x <= r ;x++)
        {
            if(distance(x,y) <= r)
                printf("*");
            else
                printf(".");
        }    
        printf("\n");
    }
}

