#include "ascii_to_int.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int is_digit(const char c)
{
    if (c < '0' || c > '9')
        return 0;

    return 1;
}

atoi_status ascii_to_int(const char *src, int *out)
{
    if (!src || !out)
        return ATOI_ERR_WRONG_PTR;

    int sign = 1;
    size_t i = 0;
    int result = 0;

    if (src[i] == '-') {
        sign = -1;
        i++;
    } else if (src[i] == '+')
        i++;

    for (; src[i] != '\0'; ++i) {
        if (!is_digit(src[i]))
            return ATOI_ERR_CHAR_NO_DIGIT;

        int digit = src[i] - '0';

        if (sign == 1) {
            if (result > (INT_MAX - digit) / 10)
                return ATOI_ERR_OUT_OF_RANGE;
        } else {
            if (result > (-(INT_MIN + digit)) / 10)
                return ATOI_ERR_OUT_OF_RANGE;
        }

        result = result * 10 + digit;
    }

    *out = result * sign;
    return ATOI_OK;
}

