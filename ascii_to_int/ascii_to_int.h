#ifndef ASCII_TO_INT_H
#define ASCII_TO_INT_H

typedef enum {
    ATOI_OK                     = 0,
    ATOI_ERR_WRONG_PTR          = 1,
    ATOI_ERR_CHAR_NO_DIGIT      = 2,
    ATOI_ERR_OUT_OF_RANGE       = 3,
} atoi_status;

int is_digit(const char c);
atoi_status ascii_to_int(const char *src, int *out);
#endif
