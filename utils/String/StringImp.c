#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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

String_status String_write_to(String *str, const char *content) {
    if (!str || !content) {
        return STRING_ERR_WRONG_PTR;
    }

    String_status status = STRING_OK;
    for (size_t i = 0; content[i] != '\0'; ++i) {
        if ((status = String_append(str, content[i])) != STRING_OK) {
            fprintf(stderr, "Error status: %d\n", status);
            return status;
        }
    }

    return STRING_OK;
}

String_status String_compare(
    String *str1,
    String *str2,
    int *are_equal
) {
    if (!str1 || !str2) {
        return STRING_ERR_WRONG_PTR;
    }

    if (str1->length != str2->length) {
        *are_equal = 0;
        return STRING_OK;
    }

    for (size_t i = 0; i < str1->length; ++i) {
        if (str1->items[i] != str2->items[i]) {
            *are_equal = 0;
            return STRING_OK;
        }
    }

    *are_equal = 1;
    return STRING_OK;
}

