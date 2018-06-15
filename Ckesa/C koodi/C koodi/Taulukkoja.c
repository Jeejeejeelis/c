//
//  Taulukkoja.c
//  C koodi
//
//  Created by Eelis Pinomaa on 30/06/2017.
//  Copyright © 2017 Eelis Pinomaa. All rights reserved.
//

#include <stdio.h>


int array_sum(int *array, int count)
{
    int sum = 0;
    for (int i = 0; i<count; i++)
    {
        sum = sum + *array[i];
        
    }
    return sum;
}

int main(){
    printf("jee");
    int valarray[] = { 10, 100, 1000 };
    int ret = array_sum(valarray, 3);
    printf("%d", ret);
    return 0;
}
