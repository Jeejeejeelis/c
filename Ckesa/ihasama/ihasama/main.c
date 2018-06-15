//
//  main.c
//  ihasama
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
        sum = sum + array[i];
        
    }
    return sum;
}

int array_reader(int *vals, int n){
    int numbers = 0;
    for (int i = 0; i<n; i++)
    {
        int luku = 0;
        if(scanf("%d", &luku)){
            vals[i] = luku;
            numbers++;
            
        } else {
            break;
        }
        
    }
    return numbers;
}

int main(){
    int valarray[] = { 10, 100, 1000 };
    int ret = array_sum(valarray, 3);
    printf("%d\n", ret);
    
    int array[10];
    int n = array_reader(array, 10);
    printf("%d numbers read\n", n);
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    
    }
    return 0;
}
