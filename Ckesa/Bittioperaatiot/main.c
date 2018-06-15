#include <stdio.h>
#include "bits.h"

/* Feel free to modify this function to test different things */

void bit_set(unsigned char* data, int idx){

	data[idx] |= 1 << 8;

}

void bit_unset(unsigned char* data, int idx){

	data[idx] &= ~(1 << 8);
}

int bit_get(const unsigned char* data, int idx){
	int bit = (data[idx] >> 8) & 1;
	if (bit == 0){
		return 0;
	} else{
		return 1;
	}
}

void print_byte(unsigned char b){
	for (int i = 7; i >= 0; i--) {
	// (1 << i) generates value where only i'th bit is set
	// value & (1 << i)) is non-zero only if i'th bit is set in value
	if (b & (1 << i))
    	printf("1");
	else
		printf("0");
	}
	
}

unsigned char bit_get_sequence(const unsigned char* data, int idx, int how_many){
	if (how_many==8){
		unsigned char tulos = data[idx];
		return tulos;
	} else {
		int i = 8 - how_many;
		unsigned char tulos = data[idx]<<i;
		tulos >> i;
		return tulos;
	}
	
}

int main(void) {

    /* bit_set tests */
    printf("\n*** Testing your bit_set function..\n");
    unsigned char arr[2] = {0, 0};

    printf("At first arr[0] == 0x%02X and arr[1] == 0x%02X\n", arr[0], arr[1]);
    // Afterwards should be: arr[0] is 0x80, arr[1] is 0.
    printf("Setting bit 0\n");
    bit_set(arr, 0);
    printf("arr[0] is 0x%02X, should be 0x80\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    // Afterwards should be: arr[0] is 0x80+0x40 (0xC0), arr[1] is 0.
    printf("Setting bit 1\n");
    bit_set(arr, 1);
    printf("arr[0] is 0x%02X, should be 0x80+0x40 == 0xC0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    // Afterwards should be: arr[0] is 0xC0+0x10 (0xD0), arr[1] is 0.
    printf("Setting bit 3\n");
    bit_set(arr, 3);
    printf("arr[0] is 0x%02X, should be 0xC0+0x10 == 0xD0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    // Afterwards should be: arr[0] is 0xD0, arr[1] is 0x40.
    printf("Setting bit 9\n");
    bit_set(arr, 9);
    printf("arr[0] is 0x%02X, should be 0xC0+0x10 == 0xD0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x40\n", arr[1]);


    
    /* for practice: make your own bit_unset tests here */
    printf("\n*** Testing your bit_unset function..\n");

    printf("At first arr[0] == 0x%02X and arr[1] == 0x%02X\n", arr[0], arr[1]);
    
    printf("Unsetting bit 9\n");
    bit_unset(arr, 9);
    printf("arr[0] is 0x%02X, should be 0xD0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    printf("Unsetting bit 3\n");
    bit_unset(arr, 3);
    printf("arr[0] is 0x%02X, should be 0xD0-0x10 == 0xC0\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    printf("Unsetting bit 1\n");
    bit_unset(arr, 1);
    printf("arr[0] is 0x%02X, should be 0xC0-0x40 == 0x80\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);

    printf("Unsetting bit 0\n");
    bit_unset(arr, 0);
    printf("arr[0] is 0x%02X, should be 0x00\n", arr[0]);
    printf("arr[1] is 0x%02X, should be 0x00\n", arr[1]);


    /* bit_get tests */
    printf("\n*** Testing your bit_get function..\n");
    printf("Setting bits 0, 1, 3 and 9\n");
    bit_set(arr, 0);
    bit_set(arr, 1);
    bit_set(arr, 3);
    bit_set(arr, 9);
    printf("Bit number 0 is %d, should be 1\n", bit_get(arr,0));
    printf("Bit number 1 is %d, should be 1\n", bit_get(arr,1));
    printf("Bit number 3 is %d, should be 1\n", bit_get(arr,3));
    printf("Bit number 9 is %d, should be 1\n", bit_get(arr,9));
    printf("Bit number 2 is %d, should be 0\n", bit_get(arr,2));
    printf("Bit number 12 is %d, should be 0\n", bit_get(arr,12));

    /* print_byte tests */
    printf("\n*** Testing your print_byte function..\n");
    unsigned char b = 0x80;
    printf("Printing out 10000000, got ");
    print_byte(b); // This should print out 10000000
    printf("\n");

    b = 0xFF;
    printf("Printing out 11111111, got ");
    print_byte(b); // This should print out 11111111
    printf("\n");
    
    /* bit_get_sequence tests */
    printf("\n*** Testing your bit_get_sequence function..\n");

    printf("Getting sequence... Should be 0x68, was 0x%02X\n", bit_get_sequence(arr, 0, 7));

    return 0;
}
