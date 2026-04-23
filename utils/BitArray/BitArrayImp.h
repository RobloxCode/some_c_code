#ifndef BITARRAYIMP_H
#define BITARRAYIMP_H

#include <stdint.h>

typedef struct {
    unsigned int items: 8;
} BitArr;

void print_bin(unsigned char num);
void set(int *out, int n);
void clear(int *out, int n);

#endif
