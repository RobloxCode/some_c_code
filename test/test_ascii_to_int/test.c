#include "../../ascii_to_int/ascii_to_int.h"
#include <stdio.h>
#include <stdnoreturn.h>
#include <stdlib.h>

void test_atoi(const char *t_src);
noreturn void display_status_err(atoi_status status);
void make_tests(void);

int main(void)
{
    make_tests();
    return EXIT_SUCCESS;
}

void test_atoi(const char *t_src)
{
    if (!t_src)
        return;

    int out = 0;
    atoi_status status = ATOI_OK;
    status = ascii_to_int(t_src, &out);
    if (status != ATOI_OK)
        printf("STATUS: %d\n", status);

    printf("string    %s\n", t_src);
    printf("int num:  %d\n", out);
}

noreturn void display_status_err(atoi_status status)
{
    fprintf(stderr, "STATUS: %d", status);
    exit(EXIT_FAILURE);
}

void make_tests(void)
{
    test_atoi("123");
    test_atoi("-42");
    test_atoi("77");
    test_atoi("2147483647");
    test_atoi("2147483648");
    test_atoi("-2147483648");
    test_atoi("-2147483649");
    test_atoi("23aa");
}
