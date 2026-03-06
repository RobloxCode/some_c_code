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
    str->items[0] = '\0';
    str->capacity = init_len;
    str->length = 0;

    return str;
}

String_status String_append(String *str, const char item) {
    if (!str) {
        return STRING_ERR_WRONG_PTR;
    }

    if (str->length + 1 >= str->capacity) {
        if (str->capacity > SIZE_MAX / 2) {
            return STRING_ERR_OVERFLOW;
        }

        size_t new_cap = str->capacity * 2;

        if (new_cap > SIZE_MAX / sizeof *str->items) {
            return STRING_ERR_OVERFLOW;
        }

        char *tmp = realloc(str->items, new_cap * sizeof *str->items);
        if (!tmp) {
            return STRING_ERR_REALLOC;
        }

        str->items = tmp;
        str->capacity = new_cap;
    }

    str->items[str->length] = item;
    str->length++;
    str->items[str->length] = '\0';

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
    fprintf(stdout, "%s\n", str->items);
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
    const String *str1,
    const String *str2,
    int *are_equal
) {
    if (!str1 || !str2 || !are_equal) {
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

size_t String_len(const String *str) {
    if (!str) {
        return 0;
    }

    return str->length;
}

String_status String_clear(String *str) {
    if (!str) {
        return STRING_ERR_WRONG_PTR;
    }

    str->length = 0;
    str->items[0] = '\0';
    return STRING_OK;
}

const char *String_c_str(const String *str) {
    if (!str) {
        return NULL;
    }

    return str->items;
}

