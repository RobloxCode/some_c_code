#ifndef STRINGIMP_H
#define STRINGIMP_H
#include <stdlib.h>

typedef enum {
    STRING_OK,
    STRING_ERR_WRONG_PTR,
    STRING_ERR_REALLOC,
    STRING_ERR_OVERFLOW,
} Str_status;

typedef struct {
    char *items;

    // number of characters (not counting the \0)
    size_t length;

    // allocated memory
    size_t capacity;
} String;

String *string_create(const size_t init_len);
Str_status string_append_char(String *dst, const char src);
Str_status string_free(String **str);
Str_status string_println(const String *str);
Str_status string_append_cstr(String *dst, const char *src);
Str_status string_compare(const String *str1, const String *str2, int *result);
size_t string_len(const String *str);
Str_status string_clear(String *str);
const char *string_cstr(const String *str);

#endif
