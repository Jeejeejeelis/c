
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int *join_arrays(unsigned int lkm1, int *o1, unsigned int lkm2, int *o2, unsigned int lkm3, int *o3){
	int alkiot = lkm1+lkm2+lkm3;
	int *lista;
	lista = (int*)malloc(alkiot * sizeof(int));
	memcpy(lista, o1, lkm1*sizeof(int));
	memcpy(lista+lkm1, o2, lkm2*sizeof(int));
	memcpy(lista+lkm1+lkm2, o3, lkm3*sizeof(int));
	return lista;

}