/* 
 * File:   testi.c
 * Author: hautamt2
 *
 * Created on 10. kesäkuuta 2014, 14:54
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(void) {
    char a = 10;
    float b = 1.111;
    char* d = &a;
    *d = &b;
    return (EXIT_SUCCESS);
}

