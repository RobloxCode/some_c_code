#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#define MAX_DIGIT_LEN 9
#define MAX_DIGITS_IN_EXPRESSION 10

typedef struct {
    int *items;
    size_t len;
} IntArray;

int ascii_to_int(const char *str, int *result);
size_t get_str_len(char *str);
int clear_str(char *str);
int is_digit(char c);
int is_operator(char c);
int is_space(char c);

int parse_exp(char *exp, IntArray *digits);
int evaluate_exp(char *exp, int *result);

int main(void) {
    // if (argc != 2) {
    //     fprintf(stderr,
    //         "USAGE:\n"
    //         "./d6 [some expression]\n"
    //         "ex:\n"
    //         "./d6 \"1 + 1\"\n"
    //     );
    //     return EXIT_FAILURE;
    // }

    char *expression = "132 + 43 - 54";
    int result = 0;
    if (evaluate_exp(expression, &result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int ascii_to_int(const char *str, int *result) {
    if (!str) {
        return -1;
    }

    size_t i = 0;
    int sign = 1;

    if (str[i] == '-') {
        i++;
        sign = -1;
    } else if (str[i] == '+') {
        i++;
    }

    for (; str[i] != '\0'; ++i) {
        if (!is_digit(str[i])) {
            return -1;
        }

        int digit = str[i] - '0';

        if (sign == 1) {
            if (*result > (INT_MAX - digit) / 10) {
                return -1;
            }
        } else {
            if (*result > (-(INT_MIN + digit)) / 10) {
                return -1;
            }
        }

        *result = *result * 10 + digit;
    }

    *result = *result * sign;
    return 0;
}

size_t get_str_len(char *str) {
    if (!str) {
        return 0;
    }

    size_t i = 0;
    while (str[++i]) {
        ;;
    }
    return i;
}

int clear_str(char *str) {
    if (!str) {
        return -1;
    }

    for (size_t i = 0; str[i] != '\0'; ++i) {
        str[i] = '\0';
    }

    return 0;
}

int is_digit(char c) {
    if (c < '0' || c > '9') {
        return 0;
    }
    return 1;
}

int is_operator(char c) {
    if (c == '+' || c == '-' || c == '/' || c == '*') {
        return 1;
    }
    return 0;
}

int is_space(char c) {
    return c == ' ';
}

int parse_exp(char *exp, IntArray *digits) {
    if (!exp) {
        return -1;
    }

    int atoi_res = 0;
    char ascii_cur_digit[MAX_DIGIT_LEN] = {'\0'};
    size_t char_append_pos = 0;
    size_t digit_append_pos = 0;

    for (size_t i = 0; i < get_str_len(exp); ++i) {
        if (is_operator(exp[i]) || exp[i + 1] == '\0') {
            if ((ascii_to_int(ascii_cur_digit, &atoi_res)) < 0) {
                return -1;
            }

            digits->items[digit_append_pos] = atoi_res;
            digit_append_pos++;
            atoi_res = 0;
            char_append_pos = 0;
            clear_str(ascii_cur_digit);
            continue;
        } else if (is_space(exp[i])) {
            continue;
        } if (is_digit(exp[i])) {
            ascii_cur_digit[char_append_pos] = exp[i];
            char_append_pos++;
        }
    }

    return 0;
}

int evaluate_exp(char *exp, int *result) {
    if (!exp || !result) {
        return -1;
    }

    int items[MAX_DIGITS_IN_EXPRESSION] = {0};
    IntArray digits = (IntArray){ .items = items, .len = (size_t)MAX_DIGITS_IN_EXPRESSION };
    parse_exp(exp, &digits);

    for (size_t i = 0; i < digits.len; ++i) {
        printf("%d ", digits.items[i]);
    }

    return 0;
}
