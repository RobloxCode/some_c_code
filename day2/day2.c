/*
 * reverse a string in place
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdnoreturn.h>

void char_to_capital(char *c);
void char_to_lower(char *c);

size_t str_len(char *str);
void str_to_capital(char *str);
void str_to_lower(char *str);
int str_reverse(char *str);
int str_reverse_in_place(char *str);
int str_reverse_opt(char *str);

noreturn void display_err(char *msg);

int main(void) {
    char str[] = "abcdefg";
    puts(str);
    str_to_capital(str);
    puts(str);
    str_to_lower(str);
    puts(str);

    if (str_reverse(str) < 0)
        display_err("Error while reversing string!\n");

    puts(str);

    if (str_reverse_in_place(str) < 0)
        display_err("Error while reversing string!\n");

    puts(str);

    if (str_reverse_opt(str) < 0)
        display_err("Error while reversing string!\n");

    puts(str);

    return 0;
}

size_t str_len(char *str) {
    if (!str)
        return 0;

    size_t len = 0;
    while (str[++len])
        ;;
    return len;
}

void char_to_capital(char *c) {
    if (!c)
        return;

    *c += ('A' - 'a');
}

void char_to_lower(char *c) {
    if (!c)
        return;

    *c -= ('A' - 'a');
}

void str_to_capital(char *str) {
    if (!str)
        return;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        char_to_capital(&str[i]);
    }
}

void str_to_lower(char *str) {
    if (!str)
        return;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        char_to_lower(&str[i]);
    }
}

int str_reverse(char *str) {
    if (!str)
        return -1;

    size_t len = str_len(str);

    if (len == 0)
        return -1;

    char reversed[len];
    for (int i = (int)len - 1; i >= 0; --i) {
        reversed[len - (size_t)i - 1] = str[i];
    }

    for (size_t i = 0; i < len; ++i) {
        str[i] = reversed[i];
    }

    return 0;
}

int str_reverse_in_place(char *str) {
    if (!str)
        return -1;

    size_t len = str_len(str);

    if (len == 0)
        return -1;

    int left = 0;
    int right = (int)len - 1;

    while (left < right) {
        char tmp = str[left];
        str[left] = str[right];
        str[right] = tmp;
        left++;
        right--;
    }

    return 0;
}

int str_reverse_opt(char *str) {
    if (!str)
        return -1;

    char *left = str;
    char *right = str;

    while (*right)
        right++;

    if (right == str)
        return -1;

    right--;

    while (left < right) {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }

    return 0;
}

noreturn void display_err(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(-1);
}
