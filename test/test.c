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

    String *s3 = String_create(string_init_len);
    if (!s3) {
        goto cleanup;
    }

    // you can ignore the return status type
    String_write_to(s3, "Hello");
    printf("%s\n", String_c_str(s3));

    // saving the return status type
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
        printf(
            "the strings\n"
            "%s\n"
            "%s\n"
            "are equal\n",
            String_c_str(s1),
            String_c_str(s2)
        );
    } else {
        printf(
            "the strings\n"
            "%s\n"
            "%s",
            String_c_str(s1),
            String_c_str(s2)
        );
    }

    printf("STRING: %s\n", s1->items);
    if ((status = String_clear(s1)) != STRING_OK) {
        goto cleanup;
    }
    printf("STRING: %s\n", s1->items);

    String_write_to(s1, "new message in string");
    const char *ptr_to_char = String_c_str(s1);
    puts(ptr_to_char);

    cleanup:
        if (s1) {
            String_free(&s1);
        }

        if (s2) {
            String_free(&s2);
        }

        if (s3) {
            String_free(&s3);
        }

        if (status != STRING_OK) {
            fprintf(stderr, "Error status: %d\n", status);
            return EXIT_FAILURE;
        }

    return EXIT_SUCCESS;
}
