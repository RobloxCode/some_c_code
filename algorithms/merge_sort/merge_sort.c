#include <stdio.h>
#include <stddef.h>

void _arr_sort_helper(
    int *arr,
    int *tmp,
    const size_t left,
    const size_t mid,
    const size_t right
);
void arr_sort(
    int *arr,
    int *tmp,
    const size_t left,
    const size_t right
);
void arr_println(const int *arr, const size_t len);

int main() {
    int arr[] = {5, 2, 9, 1, 3, 3, 5, 0, 4, 6, 10, 7};
    size_t len = sizeof arr / sizeof arr[0];

    int temp[len];

    arr_sort(arr, temp, 0, (size_t)len - 1);

    arr_println(arr, len);

    printf("\n");

    return 0;
}

void _arr_sort_helper(
    int *arr,
    int *tmp,
    const size_t left,
    const size_t mid,
    const size_t right
) {
    size_t left_idx = left;
    size_t right_idx = mid + 1;
    size_t tmp_idx = left;

    while (left_idx <= mid && right_idx <= right) {
        if (arr[left_idx] <= arr[right_idx])
            tmp[tmp_idx++] = arr[left_idx++];
        else
            tmp[tmp_idx++] = arr[right_idx++];
    }

    while (left_idx <= mid)
        tmp[tmp_idx++] = arr[left_idx++];

    while (right_idx <= right)
        tmp[tmp_idx++] = arr[right_idx++];

    for (int x = (int)left; x <= (int)right; ++x)
        arr[x] = tmp[x];
}

void arr_sort(
    int *arr,
    int *tmp,
    const size_t left,
    const size_t right
) {
    if (left >= right)
        return;

    size_t mid = (left + right) / 2;

    arr_sort(arr, tmp, left, mid);
    arr_sort(arr, tmp, mid + 1, right);
    _arr_sort_helper(arr, tmp, left, mid, right);
}

void arr_println(const int *arr, const size_t len) {
    for (size_t i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}
