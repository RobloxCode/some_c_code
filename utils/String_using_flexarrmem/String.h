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

String *String_init(const size_t cap);
void String_deinit(String **str);
void String_println(const String *str);
int String_append_char(String **str, const char c);
int String_append(String **str, const char *cstr);
const char *String_to_cstr(const String *str);
size_t String_len(const String *str);

/*
 * returns 0 on success (both of the strings are equal)
 * otherwise 1
 */
int String_cmp(const String *str1, const String *str2);

void String_clear(String *str);
int String_cpy(String *dst, const String *src);
int String_concat(String **dst, const String *str1, const String *str2);

int String_join_int_arr(String *str,
                        const int *arr,
                        const size_t len,
                        const char separator);

#endif
