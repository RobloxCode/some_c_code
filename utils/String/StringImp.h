#ifndef STRINGIMP_H
#define STRINGIMP_H
#include <stdlib.h>

typedef enum {
    STRING_OK,
    STRING_ERR_WRONG_PTR,
    STRING_ERR_REALLOC,
    STRING_ERR_OVERFLOW,
} String_status;

typedef struct {
    char *items;

    // number of characters (not counting the \0)
    size_t length;

    // allocated memory
    size_t capacity;
} String;

String *String_create(const size_t init_len);
String_status String_append_char(String *dst, const char src);
String_status String_free(String **str);
String_status String_println(const String *str);
String_status String_append_cstr(String *dst, const char *src);
String_status String_compare(
    const String *str1,
    const String *str2,
    int *result
);
size_t String_len(const String *str);
String_status String_clear(String *str);
const char *String_cstr(const String *str);

#endif
