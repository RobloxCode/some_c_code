#ifndef STRING_H
#define STRING_H
#include <stddef.h>

typedef struct {
    size_t cap;

    // the variable len does not include
    // null terminator character
    size_t len;

    char items[];
} String;

String *string_init(const size_t cap);
void string_deinit(String **str);
void string_println(const String *str);
int string_append_char(String **str, const char c);
int string_append(String **str, const char *cstr);
const char *string_to_cstr(const String *str);
size_t string_len(const String *str);

/*
 * returns 0 on success (both of the strings are equal)
 * otherwise 1
 */
int string_cmp(const String *str1, const String *str2);

void string_clear(String *str);
int string_copy(String *dst, const String *src);
int string_concat(String **dst, const String *str1, const String *str2);

int string_join_int_arr(String *str, const int *arr, const size_t len,
                        const char *separator);

int string_replace(String *str, const char oldchar, char newchar);

#endif
