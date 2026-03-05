#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

typedef enum {
    STRING_OK,
    STRING_ERR_WRONG_PTR,
    STRING_ERR_REALLOC,
    STRING_ERR_OVERFLOW,
} String_status;

typedef struct {
    char *items;
    size_t length;
    size_t capacity;
} String;

String *String_create(size_t init_len);
String_status String_append(String *str, const char item);
String_status String_free(String **str);
String_status String_print(const String *str);
String_status String_write_to(
    String *str,
    const char *content,
    const size_t content_len
);

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

String *String_create(size_t init_len) {
    if (init_len == 0) {
        init_len = 1;
    }

    char *items = calloc(init_len, sizeof *items);
    if (!items) {
        return NULL;
    }

    String *str = malloc(sizeof *str);
    if (!str) {
        free(items);
        return NULL;
    }

    str->items = items;
    str->capacity = init_len;
    str->length = 0;

    return str;
}

String_status String_append(String *str, const char item) {
    if (!str) {
        return STRING_ERR_WRONG_PTR;
    }

    if (str->length == str->capacity) {
        if (str->capacity > SIZE_MAX / 2) {
            return STRING_ERR_OVERFLOW;
        }

        size_t new_len = str->capacity * 2;

        if (new_len > SIZE_MAX / sizeof *str->items) {
            return STRING_ERR_OVERFLOW;
        }

        char *tmp = realloc(str->items, new_len * sizeof *str->items);
        if (!tmp) {
            return STRING_ERR_REALLOC;
        }

        str->items = tmp;
        str->capacity = new_len;
    }

    str->items[str->length] = item;
    str->length++;

    return STRING_OK;
}

String_status String_free(String **str) {
    if (!str || !*str) {
        return STRING_ERR_WRONG_PTR;
    }

    free((*str)->items);
    free(*str);
    *str = NULL;
    return STRING_OK;
}

String_status String_print(const String *str) {
    if (!str) {
        return STRING_ERR_WRONG_PTR;
    }

    for (size_t i = 0; i < str->length; ++i) {
        printf("%c", str->items[i]);
    }

    printf("\n");
    return STRING_OK;
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
            printf("%d / %d = %d\n", num1, num2, num1 / num2);
            break;
        default:
            printf("not a valid operator\n");
    }

    String_free(&dynamic_str);
    return 0;
}
