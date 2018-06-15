//
//  draw_triangle.c
//  C koodi
//
//  Created by Eelis Pinomaa on 16/06/2017.
//  Copyright © 2017 Eelis Pinomaa. All rights reserved.
//

#include <stdio.h>
#include <math.h>

unsigned int draw_triangle(unsigned int size)
{
    int i = 0;
    while (i<size)
    {
        int a=0;
        for (a=1; a<(size-i); a++)
        {
            printf(".");
        }
        
        for (; a<=size; a++)
        {
            printf("#");
        }
        printf("\n");
        i++;
    }
    return 0 ;
}

int main(void)
{
    int luku = 0;
    printf("Anna luku:\n");
    scanf("%u", &luku);
    draw_triangle(luku);
    return 0;
}
