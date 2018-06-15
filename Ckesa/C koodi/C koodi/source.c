//
//  laskin.c
//  C koodi
//
//  Created by Eelis Pinomaa on 15/06/2017.
//  Copyright © 2017 Eelis Pinomaa. All rights reserved.
//

#include <stdio.h>
#include <math.h>

int simple_multiply()
{
    
    int eka;
    int toka;
    scanf("%d %d", &eka, &toka);
    int res = eka * toka;
    printf("%d * %d = %d\n",eka,toka,res);
    
    return 0;
}

int simple_math()
{
    float eka;
    float toka;
    char operaattori;
    
    scanf("%f %c %f", &eka, &operaattori, &toka);
    
    float res = 0;
    switch(operaattori)
    {
        case '+':
            res = eka + toka;
            printf("%.1f\n",res);
            break;
        case '-':
            res = eka - toka;
            printf("%.1f\n",res);
            break;
        case '*':
            res = eka * toka;
            printf("%.1f\n",res);
            break;
        case '/':
            res = eka / toka;
            printf("%.1f\n",res);
            break;
        default:
            printf("ERR\n");
            break;
            
    }
    return 0;
}


int main(void)
{
    
    simple_multiply();
    
    simple_math();
    
    return 0;
    
}
