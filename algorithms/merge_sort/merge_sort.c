#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// typedef struct {
//     size_t len;
//     int *values;
// } Arr;

void arr_println(const int *arr, size_t len);
void arr_cpy(
    const int *src,
    const size_t src_len,
    int *dst,
    const size_t dst_len
);

int main(void) {
    int arr[] = {2,8,5,3,9,4,1,7};
    const size_t len = sizeof arr / sizeof arr[0];

    int tmp[len];
    size_t left = len / 2;
    size_t right = len - len / 2;

    arr_println(arr, len);

    for (size_t i = 0; i < left; ++i)
        printf("%d ", arr[i]);

    printf("\n");

    for (size_t i = left; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

void arr_println(const int *arr, size_t len) {
    if (!arr)
        return;

    for (size_t i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void arr_cpy(
    const int *src,
    const size_t src_len,
    int *dst,
    const size_t dst_len
) {
    if (!src || !dst)
        return;

    if (src_len > dst_len)
        return;

    for (size_t i = 0; i < src_len; ++i)
        dst[i] = src[i];
}
