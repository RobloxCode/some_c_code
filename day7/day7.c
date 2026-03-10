#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define NUM_WORDS 5

size_t str_len(const char *str);
int is_anagram(const char *str1, const char *str2);
void print_strs(char **strs, const size_t strs_len);
int find_anagrams(
    char **words,
    const size_t words_len,
    char **out
);

int main(void) {
    char *words[NUM_WORDS] = {
        "eggs", "plant", "cat", "gsge", "tac"
    };
    char *anagrams[NUM_WORDS];

    if (find_anagrams(words, NUM_WORDS, anagrams) < 0) {
        return EXIT_FAILURE;
    }

    print_strs(anagrams, (size_t)NUM_WORDS);

    return EXIT_SUCCESS;
}

size_t str_len(const char *str) {
    if (!str) {
        return 0;
    }

    size_t i = 0;
    while (str[i]) {
        i++;
    }

    return i;
}

int is_anagram(const char *str1, const char *str2) {
    if (!str1 || !str2) {
        return 0;
    }

    if (str_len(str1) != str_len(str2)) {
        return 0;
    }

    int sum_s1 = 0;
    int sum_s2 = 0;

    for (size_t i = 0; str1[i] != '\0'; ++i) {
        sum_s1 += str1[i];
        sum_s2 += str2[i];
    }

    if (sum_s1 == sum_s2) {
        return 1;
    }

    return 0;
}

void print_strs(char **strs, const size_t strs_len) {
    if (!strs || !*strs) {
        return;
    }

    for (size_t i = 0; i < strs_len; ++i) {
        printf("%s\n", strs[i]);
    }

    printf("\n");
}

int find_anagrams(
    char **words,
    const size_t words_len,
    char **out
) {
    if (!words || !*words || !out || !*out) {
        return -1;
    }

    size_t out_idx = 0;
    for (size_t i = 0; i < words_len; ++i) {
        for (size_t j = i + 1; j < words_len; ++j) {
            if (is_anagram(words[i], words[j])) {
                out[out_idx] = words[i];
            }
        }
    }

    return 0;
}
