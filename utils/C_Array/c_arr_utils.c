#include "c_arr_utls.h"
#include <limits.h>
#include <stdio.h>

static void _arr_sort_helper(int *arr,
    int *tmp,
    const size_t left,
    const size_t mid,
    const size_t right)
{
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
    const size_t right)
{
    if (left >= right)
        return;

    size_t mid = (left + right) / 2;

    arr_sort(arr, tmp, left, mid);
    arr_sort(arr, tmp, mid + 1, right);
    _arr_sort_helper(arr, tmp, left, mid, right);
}

void arr_println(const int *arr, size_t len)
{
    if (!arr)
        return;

    for (size_t i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void arr_clear(int *arr, const size_t len)
{
    for (size_t i = 0; i < len; ++i)
        arr[i] = 0;
}

void arr_add(
    int *res,
    const size_t res_len,
    const int *arr1,
    const size_t arr1_len,
    const int *arr2,
    const size_t arr2_len)
{
    if (!res || !arr1 || !arr2)
        return;

    if (res_len < MAX(arr1_len, arr2_len))
        return;

    size_t min_len = MIN(arr1_len, arr2_len);

    for (size_t i = 0; i < min_len; ++i)
        res[i] = arr1[i] + arr2[i];

    for (size_t i = min_len; i < arr1_len; ++i)
        res[i] = arr1[i];

    for (size_t i = min_len; i < arr2_len; ++i)
        res[i] = arr2[i];
}

void arr_sub(
    int *res,
    const size_t res_len,
    const int *arr1,
    const size_t arr1_len,
    const int *arr2,
    const size_t arr2_len)
{
    if (!res || !arr1 || !arr2)
        return;

    if (res_len < MAX(arr1_len, arr2_len))
        return;

    size_t min_len = MIN(arr1_len, arr2_len);

    for (size_t i = 0; i < min_len; ++i)
        res[i] = arr1[i] - arr2[i];

    for (size_t i = min_len; i < arr1_len; ++i)
        res[i] = arr1[i];

    for (size_t i = min_len; i < arr2_len; ++i)
        res[i] = arr2[i];
}

void arr_mul(
    int *res,
    const size_t res_len,
    const int *arr1,
    const size_t arr1_len,
    const int *arr2,
    const size_t arr2_len)
{
    if (!res || !arr1 || !arr2)
        return;

    if (res_len < MAX(arr1_len, arr2_len))
        return;

    size_t min_len = MIN(arr1_len, arr2_len);

    for (size_t i = 0; i < min_len; ++i)
        res[i] = arr1[i] * arr2[i];

    for (size_t i = min_len; i < arr1_len; ++i)
        res[i] = arr1[i];

    for (size_t i = min_len; i < arr2_len; ++i)
        res[i] = arr2[i];
}

void arr_div(
    int *res,
    const size_t res_len,
    const int *arr1,
    const size_t arr1_len,
    const int *arr2,
    const size_t arr2_len)
{
    if (!res || !arr1 || !arr2)
        return;

    if (res_len < MAX(arr1_len, arr2_len))
        return;

    size_t min_len = MIN(arr1_len, arr2_len);

    for (size_t i = 0; i < min_len; ++i) {
        if (arr2[i] == 0)
            continue;

        res[i] = arr1[i] / arr2[i];
    }

    for (size_t i = min_len; i < arr1_len; ++i)
        res[i] = arr1[i];

    for (size_t i = min_len; i < arr2_len; ++i)
        res[i] = arr2[i];
}

void arr_reverse(int *arr, const size_t len)
{
    if (!arr || len == 0)
        return;

    size_t left = 0;
    size_t right = len - 1;

    while (left < right) {
        int tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;
        left++;
        right--;
    }
}

void arr_copy(
    int *dst,
    const size_t dst_len,
    const int *src,
    const size_t src_len)
{
    if (!dst || !src)
        return;

    if (src_len > dst_len)
        return;

    for (size_t i = 0; i < src_len; ++i)
        dst[i] = src[i];
}
