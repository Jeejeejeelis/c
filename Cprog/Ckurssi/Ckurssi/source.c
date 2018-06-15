//
//  source.c
//  Ckurssi
//
//  Created by Eelis Pinomaa on 21/01/2017.
//  Copyright © 2017 Eelis Pinomaa. All rights reserved.
//

#include <stdio.h>
#include <math.h>

double vectorlength(double X, double Y, double Z)
{
    double XY = sqrt(pow(X, 2)+pow(Y, 2));
    double XYZ = sqrt(pow(XY,2)+pow(Z,2));
    return XYZ;
}

int main(void)
{
    double length = vectorlength(2, 3, 4);
    printf("length: %f", length);
    return 0;
}
