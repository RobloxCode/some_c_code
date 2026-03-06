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

String *String_create(size_t init_len);
String_status String_append(String *str, const char item);
String_status String_free(String **str);
String_status String_print(const String *str);
String_status String_write_to(String *str, const char *content);
String_status String_compare(
    const String *str1,
    const String *str2,
    int *are_equal
);
size_t String_len(const String *str);
String_status String_clear(String *str);
const char *String_c_str(const String *str);

#endif
