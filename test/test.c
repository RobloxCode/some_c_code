#include <stdio.h>
#include <stdlib.h>
#include "../utils/String/StringImp.h"

int main(void) {
    const size_t string_init_len = 10;
    int comparisson = 0;
    String_status status = STRING_OK;
    String *s1 = String_create(string_init_len);
    if (!s1) {
        goto cleanup;
    }

    String *s2 = String_create(string_init_len);
    if (!s2) {
        goto cleanup;
    }

    if ((status = String_write_to(s1, "this is the string1")) != STRING_OK) {
        goto cleanup;
    }

    if ((status = String_write_to(s2, "this is the string1")) != STRING_OK) {
        goto cleanup;
    }

    if ((status = String_compare(s1, s2, &comparisson)) != STRING_OK) {
        goto cleanup;
    }

    if (comparisson) {
        printf("the strings\n");
        String_print(s1);
        String_print(s2);
        printf("are equal\n");
    } else {
        printf("the strings\n");
        String_print(s1);
        String_print(s2);
        printf("are different\n");
    }

    cleanup:
        if (s1) {
            String_free(&s1);
        }

        if (s2) {
            String_free(&s2);
        }

        if (status != STRING_OK) {
            fprintf(stderr, "Error status: %d\n", status);
            return EXIT_FAILURE;
        }

    return EXIT_SUCCESS;
}
