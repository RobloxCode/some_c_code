#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#define COUNT_MAX_LEN 256

typedef struct {
    int *items;
    size_t len;
} IntArr;

void arr_println(const IntArr *arr);
void display_can_make_square(IntArr *arr);
int can_make_square(IntArr *arr);

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

void test_can_make_square()
{
    int items1[] = {0,0,1,1,1,1,2,3,2,3,4,5,5,1,3,9};
    IntArr arr = (IntArr){ .items = items1,
                           .len = sizeof items1 / sizeof items1[0]};

    display_can_make_square(&arr);

    int items2[] = {1,1,1,2,2,8};
    IntArr arr2 = (IntArr){ .items = items2,
                            .len = sizeof items2 / sizeof items2[0]};

    display_can_make_square(&arr2);

    int items3[] = {1,1,1,1,1,1};
    IntArr arr3 = (IntArr){ .items = items3,
                            .len = sizeof items3 / sizeof items3[0]};

    display_can_make_square(&arr3);

    int items4[] = {3};
    IntArr arr4 = (IntArr){ .items = items4,
                            .len = sizeof items4 / sizeof items4[0]};

    display_can_make_square(&arr4);

}
