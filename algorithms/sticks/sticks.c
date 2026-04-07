#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#define MAX_COUNT_LEN 256

void arr_println(const int *arr, const size_t len);
void arr_set(int *arr, const size_t len, const int val);
int arr_max(const int *arr, const size_t len);
int can_make_square(const int *arr, const size_t len);

int main(void) {
    int arr[] = {0,0,1,1,1,1,2,3,2,3,4,5,5,1,3,9};
    size_t len = sizeof arr / sizeof arr[0];

    if (can_make_square(arr, len))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}

void arr_println(const int *arr, const size_t len) {
    if (!arr)
        return;

    for (size_t i = 0; i < len; ++i)
        printf("%d ", arr[i]);

    printf("\n");
}

void arr_set(int *arr, const size_t len, const int val) {
    if (!arr)
        return;

    for (size_t i = 0; i < len; ++i)
        arr[i] = val;
}

int can_make_square(const int *arr, const size_t len) {
    if (!arr)
        return 0;

    if (len < 4)
        return 0;

    int count[MAX_COUNT_LEN];

    for (size_t i = 0; i < len; ++i) {
        count[arr[i]]++;
    }

    for (size_t i = 0; i < len; ++i) {
        if (count[i] >= 4)
            return 1;
    }

    return 0;
}
