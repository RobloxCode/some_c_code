#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../ascii_to_int/ascii_to_int.h"

#define COUNT_MAX_LEN 256
#define FILENAME "list_of_sticks.txt"
#define BUFF_MAX_LEN 256
#define FILE_CONTENT_MAX_LEN 256
#define MAX_DIGIT_COUNT 10
#define ARR_LEN(a) (sizeof (a) / sizeof(a[0]))
#define ARR_LAST(a) (a[ARR_LEN(a) - 1])

typedef struct {
    int *items;
    size_t len;
} IntArr;

void arr_println(const IntArr *arr);
void display_can_make_square(IntArr *arr);
int can_make_square(const IntArr *arr);
void display_can_make_square(IntArr *arr);
size_t get_num_new_lines(const char *str);
void load_file_content(char *buf,
                       const size_t buf_size,
                       FILE *stream);
void init_new_lines_idxs(size_t *new_lines_idxs,
                         const char *file_content,
                         const size_t starting_idx);
void parse_file_content(const char *file_content,
                        int *file_content_parsed);
int arr_contains_val(const size_t *arr,
                     const size_t len,
                     const size_t val);

void test_can_make_square(void);

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

int can_make_square(const IntArr *arr) {
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

void init_new_lines_idxs(size_t *new_lines_idxs,
                         const char *file_content,
                         const size_t starting_idx)
{
    size_t last_new_line_idx = starting_idx;
    size_t last_pos = 0;
    for (size_t i = 0; file_content[i] != '\0'; ++i) {
        if (file_content[i] != '\n' && file_content[i] != ' ')
            last_pos++;
        else if (file_content[i] == '\n')
            new_lines_idxs[last_new_line_idx++] = last_pos;
    }
}

void parse_file_content(const char *file_content,
                        int *file_content_parsed)
{
    size_t file_content_parsed_idx = 0;
    int parse_helper_buf = 0;
    char cur_digit_buf[MAX_DIGIT_COUNT] = {0};
    size_t cur_digit_buf_idx = 0;

    for (size_t i = 0; file_content[i] != '\0'; ++i) {
        char cur_char = file_content[i];

        if (cur_char == ' ' || cur_char == '\n') {
            ascii_to_int(cur_digit_buf, &parse_helper_buf);
            file_content_parsed[file_content_parsed_idx++] = parse_helper_buf;
            cur_digit_buf_idx = 0;
        } else
            cur_digit_buf[cur_digit_buf_idx++] = cur_char;
    }
}

int arr_contains_val(const size_t *arr,
                     const size_t len,
                     const size_t val)
{
    for (size_t i = 0; i < len; ++i)
        if (arr[i] == val)
            return 1;

    return 0;
}

void test_can_make_square(void)
{
    FILE *file = NULL;
    char file_content[BUFF_MAX_LEN];

    file = fopen(FILENAME, "r");
    if (!file)
        return;

    load_file_content(file_content, sizeof file_content, file);

    size_t num_new_lines = get_num_new_lines(file_content);
    int file_content_parsed[strlen(file_content)];
    size_t new_lines_idxs[num_new_lines + 1];

    memset(new_lines_idxs, 0, sizeof new_lines_idxs);
    memset(file_content_parsed, 0, sizeof file_content_parsed);

    init_new_lines_idxs(new_lines_idxs, file_content, 1);

    parse_file_content(file_content, file_content_parsed);

    puts(file_content);

    for (size_t i = 0; i < ARR_LEN(file_content_parsed); ++i) {
        if (arr_contains_val(new_lines_idxs, ARR_LEN(new_lines_idxs), (size_t)i))
            printf("\n%d", file_content_parsed[i]);
        else
            printf("%d ", file_content_parsed[i]);
    }

    fclose(file);
}
