#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#define MAX_DIGIT_LEN 9
#define MAX_DIGITS_IN_EXPRESSION 10

typedef enum {
    ATOI_OK                 = 0,
    ATOI_ERR_WRONG_PTR      = 1,
    ATOI_ERR_NO_DIGIT       = 2,
    ATOI_ERR_OUT_OF_RANGE   = 3,
} atoi_status;

typedef enum {
    GET_OP_OK                   = 0,
    GET_OP_ERR_WRONG_PTR        = 1,
    GET_OP_ERR_NO_OP_FOUND      = 2,
} get_operator_status;

typedef enum {
    GET_DIGITS_OK                   = 0,
    GET_DIGITS_ERR_WRONG_PTR        = 1,
    GET_DIGITS_ERR_ATOI_ERR         = 2,
    GET_DIGITS_ERR_DIGIT_OVERFLOW   = 3,
} get_digits_status;

typedef enum {
    EVALEXP_OK                  = 0,
    EVALEXP_ERR_WRONG_PTR       = 1,
    EVALEXP_ERR_DIV_BY_ZERO     = 2,
    EVALEXP_ERR_HELPER_FUNC     = 3,
    EVALEXP_ERR_NOT_VALID_OP    = 4,
} evaluate_exp_status;

atoi_status ascii_to_int(const char *str, int *result);
size_t get_str_len(const char *str);
int clear_str(char *str);
int is_digit(char c);
int is_operator(char c);

get_digits_status get_digits(char *exp, int *digits);
get_operator_status get_operator(char *exp, char *operator);
evaluate_exp_status evaluate_exp(char *exp, int *result);

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

    evaluate_exp_status status = EVALEXP_OK;
    char *expression = argv[1];
    int result = 0;
    if ((status = evaluate_exp(expression, &result)) != EVALEXP_OK) {
        fprintf(stderr, "Error EVALEXP_STATUS: %d\n", status);
        return EXIT_FAILURE;
    }

    printf("result: %d\n", result);
    return EXIT_SUCCESS;
}

atoi_status ascii_to_int(const char *str, int *result) {
    if (!str || !result) {
        return ATOI_ERR_WRONG_PTR;
    }

    *result = 0;
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
            return ATOI_ERR_NO_DIGIT;
        }

        int digit = str[i] - '0';

        if (sign == 1) {
            if (*result > INT_MAX / 10 || (*result == INT_MAX / 10 && digit > INT_MAX % 10)) {
                return ATOI_ERR_OUT_OF_RANGE;
            }
        } else {
            if (*result > (-(INT_MIN + digit)) / 10) {
                return ATOI_ERR_OUT_OF_RANGE;
            }
        }

        *result = *result * 10 + digit;
    }

    *result = *result * sign;
    return ATOI_OK;
}

size_t get_str_len(const char *str) {
    if (!str) {
        return 0;
    }

    size_t i = 0;
    while (str[i]) {
        i++;
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

get_digits_status get_digits(char *exp, int *digits) {
    if (!exp || !digits) {
        return GET_DIGITS_ERR_WRONG_PTR;
    }

    atoi_status status = ATOI_OK;
    int atoi_res = 0;
    char digit_buff[MAX_DIGIT_LEN] = {'\0'};
    size_t digit_idx = 0;
    size_t buff_idx = 0;

    for (size_t i = 0; exp[i] != '\0'; ++i) {
        char exp_cur_char = exp[i];

        if (is_digit(exp_cur_char)) {
            if (buff_idx >= MAX_DIGIT_LEN - 1) {
                return GET_DIGITS_ERR_DIGIT_OVERFLOW;
            }

            digit_buff[buff_idx] = exp_cur_char;
            buff_idx++;
        }

        if (is_operator(exp_cur_char) || exp[i + 1] == '\0') {
            status = ascii_to_int(digit_buff, &atoi_res);
            if (status != ATOI_OK) {
                return GET_DIGITS_ERR_ATOI_ERR;
            }

            digits[digit_idx] = atoi_res;
            digit_idx++;
            atoi_res = 0;
            buff_idx = 0;
            clear_str(digit_buff);
        }

        if (exp_cur_char == ' ') {
            continue;
        }
    }

    return GET_DIGITS_OK;
}

get_operator_status get_operator(char *exp, char *operator) {
    if (!exp || !operator) {
        return GET_OP_ERR_WRONG_PTR;
    }

    for (size_t i = 0; exp[i] != '\0'; ++i) {
        if (is_operator(exp[i])) {
            *operator = exp[i];
            return GET_OP_OK;
        }
    }

    return GET_OP_ERR_NO_OP_FOUND;
}

evaluate_exp_status evaluate_exp(char *exp, int *result) {
    if (!exp || !result) {
        return EVALEXP_ERR_WRONG_PTR;
    }

    get_operator_status op_status = GET_OP_OK;
    get_digits_status digits_status = GET_DIGITS_OK;

    int digits[MAX_DIGITS_IN_EXPRESSION] = {0};
    char char_op = '\0';
    int num1 = 0;
    int num2 = 0;

    if ((digits_status = get_digits(exp, digits)) != GET_DIGITS_OK) {
        goto error;
    }

    if ((op_status = get_operator(exp, &char_op)) != GET_OP_OK) {
        goto error;
    }

    num1 = digits[0];
    num2 = digits[1];

    switch (char_op) {
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
                return EVALEXP_ERR_DIV_BY_ZERO;
            }

            *result = num1 / num2;
            break;
        default:
            printf("not a valid operator\n");
            return EVALEXP_ERR_NOT_VALID_OP;
    }

    return EVALEXP_OK;

    error:
    if (digits_status != GET_DIGITS_OK) {
        fprintf(stderr, "Error GET_DIGITS_STATUS: %d\n", digits_status);
    }

    if (op_status != GET_OP_OK) {
        fprintf(stderr, "Error GET_OP_STATUS: %d\n", op_status);
    }

    return EVALEXP_ERR_HELPER_FUNC;
}
