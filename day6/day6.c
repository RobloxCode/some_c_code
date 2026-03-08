#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#define MAX_DIGIT_LEN 9
#define MAX_DIGITS_IN_EXPRESSION 10

int ascii_to_int(const char *str, int *result);
size_t get_str_len(char *str);
int clear_str(char *str);
int is_digit(char c);
int is_operator(char c);

int get_digits(char *exp, int *digits);
int get_operator(char *exp, char *operator);
int evaluate_exp(char *exp, int *result);

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr,
            "USAGE:\n"
            "./d6 [some expression]\n"
            "ex:\n"
            "./d6 \"1 + 1\"\n"
        );
        return EXIT_FAILURE;
    }

    char *expression = argv[1];
    int result = 0;
    if (evaluate_exp(expression, &result) < 0) {
        return EXIT_FAILURE;
    }

    printf("result: %d\n", result);

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

int get_digits(char *exp, int *digits) {
    if (!exp || !digits) {
        return -1;
    }

    int atoi_res = 0;
    char ascii_digit_buff[MAX_DIGIT_LEN] = {'\0'};
    size_t digit_last_i = 0;
    size_t ascii_digit_buff_last_i = 0;

    for (size_t i = 0; exp[i] != '\0'; ++i) {
        char exp_cur_char = exp[i];

        if (is_digit(exp_cur_char)) {
            ascii_digit_buff[ascii_digit_buff_last_i] = exp_cur_char;
            ascii_digit_buff_last_i++;
        }

        if (is_operator(exp_cur_char) || exp[i + 1] == '\0') {
            if ((ascii_to_int(ascii_digit_buff, &atoi_res)) < 0) {
                return -1;
            }

            digits[digit_last_i] = atoi_res;
            digit_last_i++;
            atoi_res = 0;
            ascii_digit_buff_last_i = 0;
            clear_str(ascii_digit_buff);
        }
    }

    return 0;
}

int get_operator(char *exp, char *operator) {
    if (!operator) {
        return -1;
    }

    for (size_t i = 0; exp[i] != '\0'; ++i) {
        if (is_operator(exp[i])) {
            *operator = exp[i];
            return 0;
        }
    }

    return -1;
}

int evaluate_exp(char *exp, int *result) {
    if (!exp || !result) {
        return -1;
    }

    int digits[MAX_DIGITS_IN_EXPRESSION] = {0};
    char operator = '\0';

    if (get_digits(exp, digits) < 0) {
        return -1;
    }

    if (get_operator(exp, &operator) < 0) {
        return -1;
    }

    int num1 = digits[0];
    int num2 = digits[1];

    switch (operator) {
        case '+':
            *result = num1 + num2;
            break;
        case '-':
            *result = num1 - num2;
            break;
        case '*':
            *result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printf("cannot divide by 0\n");
                return -1;
            }
            *result = num1 / num2;
            break;
        default:
            printf("not a valid operator\n");
    }

    return 0;
}
