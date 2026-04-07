#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#define MAX_COUNT_LEN 256

void arr_println(const int *arr, const size_t len);
void arr_set(int *arr, const size_t len, const int val);
int arr_max(const int *arr, const size_t len);
int can_make_square(const int *arr, const size_t len);

void test_can_make_square();

int main(void) {
    test_can_make_square();
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

void display_test_info(const int *arr, const size_t len) {
    printf("arr: ");
    arr_println(arr, len);
    if (can_make_square(arr, len))
        printf("YES\n");
    else
        printf("NO\n");
}

void test_can_make_square() {
    int arr1[] = {0,0,1,1,1,1,2,3,2,3,4,5,5,1,3,9};
    size_t len1 = sizeof arr1 / sizeof arr1[0];
    display_test_info(arr1, len1);

    int arr2[] = {1,1,1,2,2,8};
    size_t len2 = sizeof arr2 / sizeof arr2[0];
    display_test_info(arr2, len2);

    int arr3[] = {1,1,1,1,1,1};
    size_t len3 = sizeof arr3 / sizeof arr3[0];
    display_test_info(arr3, len3);

    int arr4[] = {3};
    size_t len4 = sizeof arr4 / sizeof arr4[0];
    display_test_info(arr4, len4);

}
