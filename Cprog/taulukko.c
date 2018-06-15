#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>

int *dynamic_reader(unsigned int n)
{
    int size = n;
    int *lista;
    lista = (int*)malloc(size * sizeof(int));
    printf("Anna arvoja: \n");
    int i;
    for(i = 0; i<size; i++)
        scanf("%d", &lista[i]);
    return lista;

}

int *insert_into_array(int *arr, unsigned int num, int newval)
{   
    if(arr != NULL){
        int *newarr =realloc(arr, sizeof(int) * (num+1));
        if(!newarr){
            return NULL;
        }else{
            newarr[num] = newval;
            return newarr;
        }
    }
    else{
        return NULL;
    }

}

