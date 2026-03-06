#include <stdio.h>
#include "../utils/String/StringImp.h"

int main(void) {
    String *s = String_create(10);
    if (!s)
        return 1;

    String_write_to(s, "i wanna write to this msg");

    String_print(s);
    String_free(&s);
    return 0;
}
