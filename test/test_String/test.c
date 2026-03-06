#include <stdio.h>
#include <stdlib.h>
#include "../../utils/String/StringImp.h"

int main(void) {
    const size_t string_init_len = 10;
    int comparisson = 0;
    String_status status = STRING_OK;

    String *s1 = String_create(string_init_len);
    if (!s1)
        goto cleanup;

    String *s2 = String_create(string_init_len);
    if (!s2)
        goto cleanup;

    String *s3 = String_create(string_init_len);
    if (!s3)
        goto cleanup;

    status = String_write_to(s1, "message written to string 1 example");
    if (status != STRING_OK)
        goto cleanup;

    // we can ignore the return status code
    String_write_to(s2, "some other message for string 2");

    status = String_write_to(s3, "final message for string 3");
    if (status != STRING_OK)
        goto cleanup;

    String_print(s1);
    printf("%s\n", s2->items);
    printf("%s\n", String_c_str(s3));

    if ((status = String_clear(s1)) != STRING_OK)
        goto cleanup;

    if ((status = String_clear(s2)) != STRING_OK)
        goto cleanup;

    String_write_to(s2, "aaa");

    String_print(s1);
    String_append(s1, 'a');
    String_append(s1, 'a');
    String_append(s1, 'a');

    String_print(s1);
    printf("%s\n", s2->items);
    printf("%s\n", String_c_str(s3));

    if ((status = String_compare(s1, s2, &comparisson)) != STRING_OK)
        goto cleanup;

    if (comparisson) {
        printf(
            "s1: %s\n"
            "s2: %s\n"
            "are equal\n",
            String_c_str(s1),
            String_c_str(s2)
        );
    } else {
        printf(
            "s1: %s\n"
            "s2: %s\n"
            "are not equal\n",
            String_c_str(s1),
            String_c_str(s2)
        );
    }

    if ((status = String_compare(s2, s3, &comparisson)) != STRING_OK)
        goto cleanup;

    if (comparisson) {
        printf(
            "s2: %s\n"
            "s3: %s\n"
            "are equal\n",
            String_c_str(s2),
            String_c_str(s3)
        );
    } else {
        printf(
            "s2: %s\n"
            "s3: %s\n"
            "are not equal\n",
            String_c_str(s2),
            String_c_str(s3)
        );
    }

    printf("len s1: %zu\n", String_len(s1));
    printf("len s2: %zu\n", String_len(s2));
    printf("len s3: %zu\n", String_len(s3));

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
