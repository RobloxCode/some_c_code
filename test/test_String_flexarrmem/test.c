#include "../../utils/String_using_flexarrmem/String.h"
#include <stdio.h>

void test_String();

int main(void) {
    test_String();
    return 0;
}

void test_String() {
    String *s = String_init(10);
    if (!s) {
        printf("NULL\n");
        return;
    }

    String_println(s);

    String_append_char(&s, 'h');
    String_append_char(&s, 'e');
    String_append_char(&s, 'l');
    String_append_char(&s, 'l');
    String_append_char(&s, 'o');

    printf("cap: %zu\n", s->cap);
    printf("len: %zu\n", s->len);
    String_println(s);

    String_append(&s,
            "this text should be something really long i guess");
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

    String_append(&s2, (char *)String_to_cstr(s));

    if (String_cmp(s, s2) == 0)
        printf("the strings\n%s\n%s\nare the same\n",
                String_to_cstr(s), String_to_cstr(s2));
    else
        printf("the strings are not the same\n");

cleanup:
    String_deinit(&s);
    String_deinit(&s2);
    return;
}
