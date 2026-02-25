#include <stdio.h>
#include <stddef.h>

size_t str_len(char *str);

void char_to_capital(char *c);
void char_to_lower(char *c);

void str_to_capital(char *str);
void str_to_lower(char *str);
void str_reverse(char *str);

int main(void) {
    char str[] = "abcdefg";
    puts(str);
    str_to_capital(str);
    puts(str);
    str_to_lower(str);
    puts(str);

    str_reverse(str);
    puts(str);

    return 0;
}

size_t str_len(char *str) {
    size_t len = 0;
    while (str[++len])
        ;;
    return len;
}

void char_to_capital(char *c) {
    *c += ('A' - 'a');
}

void char_to_lower(char *c) {
    *c -= ('A' - 'a');
}

void str_to_capital(char *str) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        char_to_capital(&str[i]);
    }
}

void str_to_lower(char *str) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        char_to_lower(&str[i]);
    }
}

void str_reverse(char *str) {
    size_t len = str_len(str);
    char reversed[len];
    for (int i = (int)len - 1; i >= 0; --i) {
        reversed[len - (size_t)i - 1] = str[i];
    }

    for (size_t i = 0; i < len; ++i) {
        str[i] = reversed[i];
    }
}
