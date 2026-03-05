#include <stdio.h>
#include <stdlib.h>
#define MAX_CHARS_LEN 1024

size_t get_str_len(char *str);
int parse_str(char *str);

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr,
            "USAGE:\n"
            "./d6 [some expression]\n"
            "ex:\n"
            "./d6 \"1 + 1\"\n"
        );
        return EXIT_FAILURE;
    }

    char *usr_str = argv[1];
    if (parse_str(usr_str) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

size_t get_str_len(char *str) {
    if (!str) {
        return (size_t)0;
    }

    size_t len = 0;
    while (str[++len]) {
        ;;
    }

    return len;
}

int parse_str(char *str) {
    if (!str) {
        return -1;
    }

    char characters[MAX_CHARS_LEN];

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] != ' ') {
            characters[i] = str[i];
        }
    }

    puts(characters);
    return 0;
}

