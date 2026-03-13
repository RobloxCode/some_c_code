#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define NUM_WORDS 5
#define ANAGRAMS_MAX_LEN (NUM_WORDS * 2)
#define ANAGRAM_FREQ_LEN 256

size_t str_len(const char *str);
int is_anagram_count_chars(const char *str1, const char *str2);
int is_anagram(const char *str1, const char *str2);
int print_strs(char *const *strs, const size_t strs_len);
int find_anagrams(
    char **words,
    const size_t words_len,
    char **out,
    size_t *out_cap
);

int main(void) {
    char *words[NUM_WORDS] = {"eggs", "plant", "cat", "gsge", "tac"};
    size_t anagrams_found = 0;
    char *anagrams[ANAGRAMS_MAX_LEN] = {0};

    if (is_anagram_count_chars("hello", "hello")) {
        puts("they're anagrams");
    } else {
        puts("they're not anagrams");
    }

    // if (find_anagrams(words, NUM_WORDS, anagrams, &anagrams_found) < 0) {
    //     return EXIT_FAILURE;
    // }

    if (print_strs(anagrams, anagrams_found) < 0) {
        return EXIT_FAILURE;
    }

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

int is_anagram_count_chars(const char *str1, const char *str2) {
    if (!str1 || !str2) {
        return 0;
    }

    int freq[ANAGRAM_FREQ_LEN] = {0};

    for (size_t i = 0; str1[i] != '\0'; ++i) {
        char cur_char = str1[i];
        freq[(int)cur_char]++;
    }

    for (size_t i = 0; str2[i] != '\0'; ++i) {
        char cur_char = str2[i];
        freq[(int)cur_char]--;
    }

    for (size_t i = 0; i < ANAGRAM_FREQ_LEN; ++i) {
        if (freq[i] != 0) {
            return 0;
        }
    }

    return 1;
}

int is_anagram(const char *str1, const char *str2) {
    if (!str1 || !str2) {
        return 0;
    }

    if (strlen(str1) != strlen(str2)) {
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

int print_strs(char *const *strs, const size_t strs_len) {
    if (!strs) {
        return -1;
    }

    for (size_t i = 0; i < strs_len; ++i) {
        if (strs[i]) {
            printf("%s\n", strs[i]);
        }
    }

    printf("\n");
    return 0;
}

int find_anagrams(
    char **words,
    const size_t words_len,
    char **out,
    size_t *out_cap
) {
    if (!words || *out || !out_cap) {
        return -1;
    }

    *out_cap = 0;
    size_t out_idx = 0;
    for (size_t i = 0; i < words_len; ++i) {
        for (size_t j = i + 1; j < words_len; ++j) {
            if (is_anagram(words[i], words[j])) {
                out[out_idx++] = words[i];
                out[out_idx++] = words[j];
                *out_cap = *out_cap + 2;
            }
        }
    }

    return 0;
}
