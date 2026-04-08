#include <stdio.h>
#include "../../utils/C_Array/c_arr_utls.h"

void c_arr_utils_test(void);

int main(void)
{
    c_arr_utils_test();
    return 0;
}

void c_arr_utils_test(void)
{
    int arr1[] = {2,4,5,9,7,1,0,3,5};
    int tmp[ARR_LEN(arr1)];
    int arr2[] = {1,2,3,4,5,5,8};
    int arr3[] = {4,5,9,7,0};
    int res[ARR_LEN(arr2) * 2];

    arr_println(arr1, ARR_LEN(arr1));
    arr_sort(arr1, tmp, 0, ARR_LEN(arr1) - 1);
    arr_println(arr1, ARR_LEN(arr1));

    printf("arr2\n");
    arr_println(arr2, ARR_LEN(arr2));
    printf("arr3\n");
    arr_println(arr3, ARR_LEN(arr3));

    arr_add(res, ARR_LEN(res), arr2, ARR_LEN(arr2), arr3, ARR_LEN(arr3));
    arr_println(res, ARR_LEN(res));
    arr_clear(res, ARR_LEN(res));

    arr_sub(res, ARR_LEN(res), arr2, ARR_LEN(arr2), arr3, ARR_LEN(arr3));
    arr_println(res, ARR_LEN(res));
    arr_clear(res, ARR_LEN(res));

    arr_mul(res, ARR_LEN(res), arr2, ARR_LEN(arr2), arr3, ARR_LEN(arr3));
    arr_println(res, ARR_LEN(res));
    arr_clear(res, ARR_LEN(res));

    arr_div(res, ARR_LEN(res), arr2, ARR_LEN(arr2), arr3, ARR_LEN(arr3));
    arr_println(res, ARR_LEN(res));
    arr_clear(res, ARR_LEN(res));

    arr_println(arr1, ARR_LEN(arr1));
    arr_reverse(arr1, ARR_LEN(arr1));
    arr_println(arr1, ARR_LEN(arr1));

    int cpy[ARR_LEN(arr3)];
    printf("before copy\n");
    arr_println(cpy, ARR_LEN(cpy));
    arr_copy(cpy, ARR_LEN(cpy), arr3, ARR_LEN(arr3));
    arr_println(cpy, ARR_LEN(cpy));
}
