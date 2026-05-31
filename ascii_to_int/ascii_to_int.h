#ifndef ASCII_TO_INT_H
#define ASCII_TO_INT_H

typedef enum {
    ATOI_OK,
    ATOI_ERR_WRONG_PTR,
    ATOI_ERR_CHAR_NO_DIGIT,
    ATOI_ERR_OUT_OF_RANGE,
} atoi_status;

int is_digit(const char c);
atoi_status ascii_to_int(const char *src, int *out);
#endif
