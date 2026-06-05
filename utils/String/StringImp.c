#include "StringImp.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

String *string_create(const size_t init_len) {
    if (init_len == 0) {
        return NULL;
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

Str_status string_append_char(String *dst, const char src) {
    if (!dst) {
        return STRING_ERR_WRONG_PTR;
    }

    if (dst->length + 1 >= dst->capacity) {
        if (dst->capacity > SIZE_MAX / 2) {
            return STRING_ERR_OVERFLOW;
        }

        size_t new_cap = dst->capacity * 2;

        if (new_cap > SIZE_MAX / sizeof dst->items) {
            return STRING_ERR_OVERFLOW;
        }

        char *tmp = realloc(dst->items, new_cap * sizeof *dst->items);
        if (!tmp) {
            return STRING_ERR_REALLOC;
        }

        dst->items = tmp;
        dst->capacity = new_cap;
    }

    dst->items[dst->length] = src;
    dst->length++;
    dst->items[dst->length] = '\0';

    return STRING_OK;
}

Str_status string_free(String **str) {
    if (!str || !*str) {
        return STRING_ERR_WRONG_PTR;
    }

    free((*str)->items);
    free(*str);
    *str = NULL;
    return STRING_OK;
}

Str_status string_println(const String *str) {
    if (!str) {
        return STRING_ERR_WRONG_PTR;
    }
    fprintf(stdout, "%s\n", str->items);
    return STRING_OK;
}

Str_status string_append_cstr(String *dst, const char *src) {
    if (!dst || !src) {
        return STRING_ERR_WRONG_PTR;
    }

    size_t src_len = 0;
    while (src[src_len] != '\0') {
        src_len++;
    }

    if (dst->length + src_len + 1 > dst->capacity) {
        size_t new_cap = dst->capacity;

        while (dst->length + src_len + 1 > new_cap) {
            if (new_cap > SIZE_MAX / 2) {
                return STRING_ERR_OVERFLOW;
            }

            new_cap *= 2;
        }

        char *tmp = realloc(dst->items, new_cap);
        if (!tmp) {
            return STRING_ERR_REALLOC;
        }

        dst->items = tmp;
        dst->capacity = new_cap;
    }

    for (size_t i = 0; i < src_len; i++) {
        dst->items[dst->length + i] = src[i];
    }

    dst->length += src_len;
    dst->items[dst->length] = '\0';

    return STRING_OK;
}

Str_status string_compare(const String *str1, const String *str2, int *result) {
    if (!str1 || !str2 || !result) {
        return STRING_ERR_WRONG_PTR;
    }

    if (str1->length != str2->length) {
        *result = 0;
        return STRING_OK;
    }

    for (size_t i = 0; i < str1->length; ++i) {
        if (str1->items[i] != str2->items[i]) {
            *result = 0;
            return STRING_OK;
        }
    }

    *result = 1;
    return STRING_OK;
}

size_t string_len(const String *str) {
    if (!str) {
        return 0;
    }

    return str->length;
}

Str_status string_clear(String *str) {
    if (!str) {
        return STRING_ERR_WRONG_PTR;
    }

    str->length = 0;
    str->items[0] = '\0';
    return STRING_OK;
}

const char *string_cstr(const String *str) {
    if (!str) {
        return NULL;
    }

    return str->items;
}

Str_status string_concat(String *dst, const String *str1, const String *str2);
Str_status string_copy(String *dst, const String *src);
Str_status string_substring(String *str);
