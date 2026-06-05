#include "../../utils/String/StringImp.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const size_t string_init_len = 10;
    int comparisson = 0;
    Str_status status = STRING_OK;
    String *s1 = NULL;
    String *s2 = NULL;
    String *s3 = NULL;

    s1 = string_create(string_init_len);
    if (!s1) {
        goto cleanup;
    }

    s2 = string_create(string_init_len);
    if (!s2) {
        goto cleanup;
    }

    s3 = string_create(string_init_len);
    if (!s3) {
        goto cleanup;
    }

    status = string_append_cstr(s1, "message written to string 1 example");
    if (status != STRING_OK) {
        goto cleanup;
    }

    status = string_append_cstr(s2, "some other message for string 2");
    if (status != STRING_OK) {
        goto cleanup;
    }

    status = string_append_cstr(s3, "final message for string 3");
    if (status != STRING_OK) {
        goto cleanup;
    }

    string_println(s1);
    printf("%s\n", s2->items);
    printf("%s\n", string_cstr(s3));

    if ((status = string_clear(s1)) != STRING_OK) {
        goto cleanup;
    }

    if ((status = string_clear(s2)) != STRING_OK) {
        goto cleanup;
    }

    string_append_cstr(s2, "aaa");

    string_println(s1);
    string_append_char(s1, 'a');
    string_append_char(s1, 'a');
    string_append_char(s1, 'a');

    string_println(s1);
    printf("%s\n", s2->items);
    printf("%s\n", string_cstr(s3));

    if ((status = string_compare(s1, s2, &comparisson)) != STRING_OK) {
        goto cleanup;
    }

    if (comparisson) {
        printf("s1: %s\n"
               "s2: %s\n"
               "are equal\n",
               string_cstr(s1), string_cstr(s2));
    } else {
        printf("s1: %s\n"
               "s2: %s\n"
               "are not equal\n",
               string_cstr(s1), string_cstr(s2));
    }

    if ((status = string_compare(s2, s3, &comparisson)) != STRING_OK) {
        goto cleanup;
    }

    if (comparisson) {
        printf("s2: %s\n"
               "s3: %s\n"
               "are equal\n",
               string_cstr(s2), string_cstr(s3));
    } else {
        printf("s2: %s\n"
               "s3: %s\n"
               "are not equal\n",
               string_cstr(s2), string_cstr(s3));
    }

    printf("len s1: %zu\n", string_len(s1));
    printf("len s2: %zu\n", string_len(s2));
    printf("len s3: %zu\n", string_len(s3));

cleanup:
    if (s1) {
        string_free(&s1);
    }

    if (s2) {
        string_free(&s2);
    }

    if (s3) {
        string_free(&s3);
    }

    if (status != STRING_OK) {
        fprintf(stderr, "Error status: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
