#include "../../utils/SafeMalloc/SafeMalloc.h"
// #include "../../utils/C_Array/c_arr_utls.h"
#include <stdlib.h>

int main(void)
{
    float *grades = safe_malloc(10 * sizeof *grades);
    int *nums = safe_calloc(10, sizeof *nums);

    free(grades);
    free(nums);
    return EXIT_SUCCESS;
}

