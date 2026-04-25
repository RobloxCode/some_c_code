#ifndef BITARRAYIMP_H
#define BITARRAYIMP_H

struct u8_BitArr {
    unsigned int items: 8;
} __attribute__((packed));

void print_bin(unsigned char num);

int u8_BitArr_print(struct u8_BitArr *ba);
int u8_BitArr_set(struct u8_BitArr *ba, int n);
int u8_BitArr_clear(struct u8_BitArr *ba, int n);

#endif
