#ifndef AALTO_BITS_H
#define AALTO_BITS_H

int bit_get(const unsigned char* data, int idx);
void bit_set(unsigned char* data, int idx);
void bit_unset(unsigned char* data, int idx);
unsigned char bit_get_sequence(const unsigned char* data, int idx, int how_many);
void print_byte(unsigned char b);

#endif
