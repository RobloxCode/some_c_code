#include "../../utils/Slice/Slice.h"

#include <stdio.h>

void test_stack_allocated_slice(int *src, size_t srclen, size_t start,
                                size_t end);
void test_heap_allocated_slice(int *src, size_t srclen, size_t start,
                               size_t end);

int main(void) {
    int nums[] = {1, 2, 3, 4, 5};
    size_t len = sizeof nums / sizeof nums[0];

    test_stack_allocated_slice(nums, len, 1, 3);
    test_stack_allocated_slice(nums, len, 3, 3);
    test_stack_allocated_slice(nums, len, 3, 0);
    test_heap_allocated_slice(nums, len, 0, 3);

    return 0;
}

void test_stack_allocated_slice(int *src, size_t srclen, size_t start,
                                size_t end) {
    iSlice slice;
    if (i_slice_init(&slice, src, srclen, start, end) != 0) {
        printf("error initialializing slice\n");
        return;
    }

    printf("stack allocated slice: ");
    i_slice_println(&slice);
}

void test_heap_allocated_slice(int *src, size_t srclen, size_t start,
                               size_t end) {
    iSlice *slice = i_slice_make(src, srclen, start, end);
    if (!slice) {
        return;
    }

    printf("heap allocated slice: ");
    i_slice_println(slice);

    i_slice_deinit(&slice);
}
