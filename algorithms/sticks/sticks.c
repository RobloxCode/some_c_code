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

    for (size_t i = 0; i < arr->len; ++i) {
        if (count[i] >= 4)
            return 1;
    }

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

size_t str_get_num_lines(const char *str)
{
    if (!str)
        return 0;

    size_t num_lines = 0;
    for (size_t i = 0; str[i] != '\0'; ++i)
        if (str[i] == '\n')
            num_lines++;

    return num_lines;
}

void test_can_make_square()
{
    FILE *file = NULL;
    char buff[BUFF_MAX_LEN];
    size_t bytes_read = 0;
    size_t num_lines = 0;

    file = fopen(FILENAME, "r");
    if (!file)
        return;

    while ((bytes_read = fread(buff, sizeof(char), sizeof buff, file)) != 0)
        buff[bytes_read] = '\0';

    num_lines = str_get_num_lines(buff);

    int items[strlen(buff)];
    size_t items_idxs[num_lines];

    for (size_t i = 0, items_idxs_pos = 0; i < strlen(buff); ++i)
        if (buff[i] == '\n')
            items_idxs[items_idxs_pos++] = i;

    for (size_t i = 0; i < items_idxs[0]; ++i)
        printf("%c", buff[i]);

    for (size_t i = items_idxs[0]; i < items_idxs[1]; ++i)
        printf("%c", buff[i]);

    fclose(file);
}
