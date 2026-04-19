#include <stddef.h>
#include <stdio.h>
#include <string.h>

size_t longest_common_subsequence(char *s1, char *s2);
void test_longest_common_subsequence(char *s1, char *s2);

int main(void)
{
    test_longest_common_subsequence("abcde", "ace");
    test_longest_common_subsequence("aoeuidhts", "auds");
    test_longest_common_subsequence("sometext\n", "eu\n");
    test_longest_common_subsequence("\nsometext", "eu\n");
    return 0;
}

size_t longest_common_subsequence(char *s1, char *s2)
{
    if (!s1 || !s2)
        return 0;

    size_t s1_len = strlen(s1);
    size_t s2_len = strlen(s2);

    size_t longest = 0;
    size_t s2_last_letter_idx = 0;
    for (size_t i = 0; i < s1_len; ++i) {
        for (size_t j = s2_last_letter_idx; j < s2_len; ++j) {
            if (s1[i] == s2[j]) {
                longest++;
                s2_last_letter_idx++;
            }
        }
    }

    return longest;
}

void test_longest_common_subsequence(char *s1, char *s2)
{
    size_t longest = longest_common_subsequence(s1, s2);
    printf("longest common subsequence: %zu\n", longest);
}
