#ifndef C_ARR_UTILS_H
#define C_ARR_UTILS_H
#include <stddef.h>

#define ARR_LEN(a) (sizeof a / sizeof a[0])
#define MIN(a, b) ((a) < (b) ? a : b)
#define MAX(a, b) ((a) > (b) ? a : b)

void arr_println(const int *arr, size_t len);
void arr_sort(
    int *arr,
    int *tmp,
    const size_t left,
    const size_t right);
void arr_add(
    int *res,
    const size_t res_len,
    const int *arr1,
    const size_t arr1_len,
    const int *arr2,
    const size_t arr2_len);
#endif
