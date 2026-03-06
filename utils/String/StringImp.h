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
    size_t length;
    size_t capacity;
} String;

String *String_create(size_t init_len);
String_status String_append(String *str, const char item);
String_status String_free(String **str);
String_status String_print(const String *str);
String_status String_write_to(String *str, const char *content);
String_status String_compare(
    String *str1,
    String *str2,
    int *are_equal
);

#endif
