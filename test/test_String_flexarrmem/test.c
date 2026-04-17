#include "../../utils/String_using_flexarrmem/String.h"
#include <stdio.h>

void test_String();

int main(void)
{
    test_String();
    return 0;
}

void test_String()
{
    String *s = String_init(10);
    if (!s) {
        printf("NULL\n");
        return;
    }

    String_println(s);

    if (String_append_char(&s, 'h') != 0) goto cleanup;
    if (String_append_char(&s, 'e') != 0) goto cleanup;
    if (String_append_char(&s, 'l') != 0) goto cleanup;
    if (String_append_char(&s, 'l') != 0) goto cleanup;
    if (String_append_char(&s, 'o') != 0) goto cleanup;

    printf("cap: %zu\n", s->cap);
    printf("len: %zu\n", s->len);
    String_println(s);

    if (String_append(&s,
            " this text should be something really long i guess"))
        goto cleanup;

    String_println(s);

    printf("cap: %zu\n", s->cap);
    printf("len: %zu\n", s->len);

    const char *cstr= NULL;
    cstr = String_to_cstr(s);
    puts(cstr);

    printf("len: %zu\n", String_len(s));

    String *s2 = String_init(s->len);
    if (!s2)
        goto cleanup;

    if (String_append(&s2, (char *)String_to_cstr(s)) != 0)
        goto cleanup;

    if (String_cmp(s, s2) == 0)
        printf("the strings\n%s\n%s\nare the same\n",
                String_to_cstr(s), String_to_cstr(s2));
    else
        printf("the strings are not the same\n");

    puts("s");
    String_println(s);
    printf("clear string\n");
    String_clear(s);
    String_println(s);

    if (String_append(&s, "new string") != 0)
        goto cleanup;

    String_println(s);

    puts("s2");
    String_println(s2);

    printf("len s: %zu\n", s->len);
    printf("len s2: %zu\n", s2->len);

    String_cpy(s2, s);
    puts("s");
    String_println(s);
    puts("s2");
    String_println(s2);
    printf("len s2: %zu\n", s2->len);

    String *s3 = String_init(10);
    if (!s3)
        goto cleanup;

    if (String_concat(&s3, s, s2) != 0)
        goto cleanup;

    puts("coctatinated string s3:");
    String_println(s3);

    if (String_append(&s3, " some extra text") != 0)
        goto cleanup;
    String_println(s3);

    if (String_concat(&s3, s, s2) != 0)
        goto cleanup;

    String_println(s3);

    printf("joining\n");
    int arr[] = {1,2,3,4,5,7};
    if (String_join_int_arr(s, arr, sizeof arr / sizeof arr[0], ":)") != 0)
        goto cleanup;

    String_println(s);

cleanup:
    String_deinit(&s);
    String_deinit(&s2);
    String_deinit(&s3);
    return;
}
