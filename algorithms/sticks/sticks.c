#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define COUNT_MAX_LEN 256
#define FILENAME "list_of_sticks.txt"
#define BUFF_MAX_LEN 256
#define FILE_CONTENT_MAX_LEN 256

typedef struct {
    int *items;
    size_t len;
} IntArr;

void arr_println(const IntArr *arr);
void display_can_make_square(IntArr *arr);
int can_make_square(IntArr *arr);

size_t str_get_num_lines(const char *str);

void test_can_make_square();

int main(void)
{
    test_can_make_square();
    return 0;
}

void arr_println(const IntArr *arr)
{
    if (!arr)
        return;

    for (size_t i = 0; i < arr->len; ++i)
        printf("%d ", arr->items[i]);

    printf("\n");
}

int can_make_square(IntArr *arr) {
    if (!arr)
        return 0;

    if (arr->len < 4)
        return 0;

    int count[COUNT_MAX_LEN];

    for (size_t i = 0; i < arr->len; ++i)
        count[arr->items[i]]++;

    for (size_t i = 0; i < arr->len; ++i)
        if (count[i] >= 4)
            return 1;

    return 0;
}

void display_can_make_square(IntArr *arr)
{
    printf("arr: ");
    arr_println(arr);
    if (can_make_square(arr))
        printf("YES\n");
    else
        printf("NO\n");
}

size_t get_num_new_lines(const char *str)
{
    if (!str)
        return 0;

    size_t num_lines = 0;
    for (size_t i = 0; str[i] != '\0'; ++i)
        if (str[i] == '\n')
            num_lines++;

    return num_lines;
}

void load_file_content(char *buf,
                       const size_t buf_size,
                       FILE *stream)
{
    if (!buf || !stream)
        return;

    size_t bytes_read = 0;

    while ((bytes_read = fread(buf,
                               sizeof(char),
                               buf_size,
                               stream)) != 0)
        buf[bytes_read] = '\0';
}

void init_new_lines_idxs(size_t *new_lines_idxs, const char *file_content)
{
    size_t last_new_line_idx = 0;
    for (size_t i = 0; file_content[i] != '\0'; ++i)
        if (file_content[i] == '\n')
            new_lines_idxs[last_new_line_idx++] = i;
}

void test_can_make_square()
{
    FILE *file = NULL;
    char file_content[BUFF_MAX_LEN];
    size_t num_new_lines = 0;

    file = fopen(FILENAME, "r");
    if (!file)
        return;

    load_file_content(file_content, sizeof file_content, file);
    num_new_lines = get_num_new_lines(file_content);

    int file_content_parsed[strlen(file_content)];
    size_t new_lines_idxs[num_new_lines];

    init_new_lines_idxs(new_lines_idxs, file_content);

    puts(file_content);

    puts("new lines idxs");
    for (size_t i = 0; i < num_new_lines; ++i)
        printf("%zu\n", new_lines_idxs[i]);

    fclose(file);
}
