#ifndef BITARRAYIMP_H
#define BITARRAYIMP_H

struct u8_BitArr {
    unsigned int items : 8;
} __attribute__((packed));

void print_bin(const unsigned char num);
int u8_bit_arr_print(const struct u8_BitArr *ba);
int u8_bit_arr_set(struct u8_BitArr *ba, int n);
int u8_bit_arr_clear(struct u8_BitArr *ba, int n);
int u8_bit_arr_get(const struct u8_BitArr *ba, const int i, int *out);

#endif
