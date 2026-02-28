#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

typedef enum {
    ATOI_OK                     = 0,
    ATOI_ERR_WRONG_PTR          = 1,
    ATOI_ERR_CHAR_NO_DIGIT      = 2,
    ATOI_ERR_OVERFLOW           = 3,
} atoi_status;

int is_digit(const char c);
atoi_status ascii_to_int(const char *src, int *out);

noreturn void display_status_err(atoi_status status);

int main(void) {
    atoi_status status = ATOI_OK;
    int int_num = 0;
    char str_num[] = "-806";

    status = ascii_to_int(str_num, &int_num);
    if (status != ATOI_OK) {
        display_status_err(status);
    }

    printf("string    %s\n", str_num);
    printf("int num:  %d\n", int_num);

    return EXIT_SUCCESS;
}

int is_digit(const char c) {
    if (c < '0' || c > '9') {
        return 0;
    }
    return 1;
}

atoi_status ascii_to_int(const char *src, int *out) {
    if (!src || !out) {
        return ATOI_ERR_WRONG_PTR;
    }

    int sign = 1;
    size_t i = 0;
    int result = 0;

    if (src[i] == '-') {
        sign = -1;
        i++;
    } else if (src[i] == '+') {
        i++;
    }

    for (; src[i] != '\0'; ++i) {
        if (!is_digit(src[i])) {
            return ATOI_ERR_CHAR_NO_DIGIT;
        }

        int digit = src[i] - '0';

        if (sign == 1) {
            if (result > (INT_MAX - digit) / 10) {
                return ATOI_ERR_OVERFLOW;
            }
        } else {
            if (result > (-(INT_MIN + digit)) / 10) {
                return ATOI_ERR_OVERFLOW;
            }
        }

        result = result * 10 + digit;
    }

    *out = result * sign;
    return ATOI_OK;
}

noreturn void display_status_err(atoi_status status) {
    fprintf(stderr, "STATUS: %d", status);
    exit(EXIT_FAILURE);
}
