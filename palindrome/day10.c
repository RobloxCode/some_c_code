#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define MAX_STR_LEN 64

int is_digit(const char c);
int is_symbol(const char c);
char char_to_low(const char c);
void str_to_low(char *str);
void str_copy(const char *src, char *dst);
int is_palindrome(const char *word);

void test_is_palindrome(char *word);

int main(void)
{
    test_is_palindrome("THTH");
    test_is_palindrome("Hello");
    test_is_palindrome("-u-");
    test_is_palindrome("Ana");
    test_is_palindrome("1221");
    test_is_palindrome("Madam");
    return EXIT_SUCCESS;
}

int is_digit(const char c)
{
    return c >= '0' && c <= '9';
}

int is_symbol(const char c)
{
    return (c >= '!' && c <= '/') ||
           (c >= ':' && c <= '@') ||
           (c >= '[' && c <= '`') ||
           (c >= '{' && c <= '~');
}

char char_to_low(const char c)
{
    if (!c)
        return '\0';

    if (is_digit(c))
        return '\0';

    if (is_symbol(c))
        return '\0';

    return c + ('a' - 'A');
}

void str_to_low(char *str)
{
    if (!str)
        return;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ' ')
            continue;
        if (str[i] >= 'a' && str[i] <= 'z')
            continue;
        if (is_symbol(str[i]))
            continue;
        if (is_digit(str[i]))
            continue;

        str[i] = char_to_low(str[i]);
    }
}

void str_copy(const char *src, char *dst)
{
    if (!src || !dst)
        return;

    size_t i = 0;
    while (src[i]) {
        dst[i] = src[i];
        i++;
    }

    dst[i] = '\0';
}

int is_palindrome(const char *word)
{
    if (!word)
        return 0;

    size_t len = 0;
    size_t left = 0;
    size_t right = 0;
    char word_low[MAX_STR_LEN] = {'\0'};
    str_copy(word, word_low);
    str_to_low(word_low);

    while (word[len])
        len++;

    right = len - 1;

    while (left <= right) {
        if (word_low[left] != word_low[right])
            return 0;

        left++;
        right--;
    }

    return 1;
}

void test_is_palindrome(char *word)
{
    if (!word)
        return;

    if (is_palindrome(word))
        printf("%s is a palindrome\n", word);
    else
        printf("%s is not a palindrome\n", word);
}
