#include "String.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

String *String_init(const size_t cap) {
    if (cap == 0)
        return NULL;

    String *str = malloc(sizeof *str + cap + 1);
    if (!str)
        return NULL;

    str->cap = cap;
    str->len = 0;
    str->items[0] = '\0';

    return str;
}

void String_deinit(String **str) {
    if (!str || !*str)
        return;

    free(*str);
    *str = NULL;
}

void String_println(const String *str) {
    if (!str)
        return;

    puts(str->items);
}

int String_append_char(String **str, const char c) {
    if (!str || !*str)
        return 1;

    if ((*str)->len + 2 > (*str)->cap) {
        size_t new_cap = (*str)->cap * 2;

        String *tmp = realloc(*str, sizeof *tmp + new_cap + 1);
        if (!tmp)
            return 1;

        tmp->cap = new_cap;
        *str = tmp;
    }

    (*str)->items[(*str)->len++] = c;
    (*str)->items[(*str)->len] = '\0';

    return 0;
}

int String_append(String **str, const char *cstr) {
    if (!str || !*str || !cstr)
        return 1;

    size_t cstr_len = 0;
    while (cstr[cstr_len])
        cstr_len++;

    if ((*str)->cap < ((*str)->len + cstr_len + 1)) {
        size_t new_cap = ((*str)->len + cstr_len) * 2;
        String *tmp = realloc(*str, sizeof *tmp + new_cap + 1);
        if (!tmp)
            return 1;

        tmp->cap = new_cap;
        *str = tmp;
    }

    for (size_t i = 0; i < cstr_len; ++i) {
        (*str)->items[i + (*str)->len] = cstr[i];
    }

    (*str)->len += cstr_len;
    (*str)->items[(*str)->len] = '\0';

    return 0;
}

const char *String_to_cstr(const String *str) {
    if (!str)
        return NULL;

    return str->items;
}

size_t String_len(const String *str) {
    if (!str)
        return 0;

    return str->len;
}

int String_cmp(const String *str1, const String *str2) {
    if (!str1 || !str2)
        return 1;

    if (str1->len != str2->len)
        return 1;

    for (size_t i = 0; i < str1->len; ++i)
        if (str1->items[i] != str2->items[i])
            return 1;

    return 0;
}

void String_clear(String *str) {
    if (!str)
        return;

    str->items[0] = '\0';
    str->len = 0;
}

int String_cpy(String *dst, const String *src) {
    if (!dst || !src)
        return 1;

    if (src->len > dst->len)
        return 1;

    String_clear(dst);
    String_append(&dst, src->items);

    return 0;
}

int String_concat(
    String **dst,
    const String *str1,
    const String *str2
) {
    if (!dst || !*dst || !str1 || !str2)
        return 1;

    if ((*dst)->cap < str1->len + str2->len) {
        size_t new_cap = str1->len + str2->len;
        String *tmp = realloc(*dst, sizeof *tmp + new_cap + 1);
        if (!tmp)
            return 1;

        tmp->cap = new_cap;
        *dst = tmp;
    }

    String_append(dst, str1->items);
    String_append(dst, str2->items);
    return 0;
}
