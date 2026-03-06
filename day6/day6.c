#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "../utils/String/StringImp.h"

int ascii_to_int(const char *str, int *out);
size_t get_str_len(char *str);
String *parse_str(char *str);
int evaluate_str(char *str);

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

    char *usr_str = argv[1];
    if (evaluate_str(usr_str) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int ascii_to_int(const char *str, int *out) {
    if (!str) {
        return -1;
    }

    size_t i = 0;
    int sign = 1;
    int result = 0;

    if (str[i] == '-') {
        i++;
        sign = -1;
    }

    for (; str[i] != '\0'; ++i) {
        int digit = str[i] - '0';
        result = result * 10 + digit;
    }

    *out = result * sign;
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

String *parse_str(char *str) {
    if (!str) {
        return NULL;
    }

    size_t str_len = get_str_len(str);
    String_status status = STRING_OK;
    String *dynamic_str = String_create(str_len);
    if (!dynamic_str) {
        return NULL;
    }

    for (size_t i = 0; i < str_len; ++i) {
        if (str[i] != ' ') {
            if ((status = String_append(dynamic_str, str[i])) != STRING_OK) {
                fprintf(stderr, "Error status: %d\n", status);
                return NULL;
            }
        }
    }

    return dynamic_str;
}

int evaluate_str(char *str) {
    if (!str) {
        return -1;
    }

    String *dynamic_str = parse_str(str);
    if (!dynamic_str) {
        return -1;
    }

    int num1 = dynamic_str->items[0] - '0';
    int num2 = dynamic_str->items[2] - '0';
    char sign = dynamic_str->items[1];

    switch (sign) {
        case '+':
            printf("%d + %d = %d\n", num1, num2, num1 + num2);
            break;
        case '-':
            printf("%d - %d = %d\n", num1, num2, num1 - num2);
            break;
        case '*':
            printf("%d * %d = %d\n", num1, num2, num1 * num2);
            break;
        case '/':
            if (num2 == 0) {
                fprintf(stderr, "cannot divide by 0\n");
                break;
            }
            printf("%d / %d = %d\n", num1, num2, num1 / num2);
            break;
        default:
            printf("not a valid operator\n");
    }

    String_free(&dynamic_str);
    return 0;
}
