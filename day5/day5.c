#include <stdio.h>
#include <stdlib.h>

void print_pascals_triangle(int n);

int main(void) {
    print_pascals_triangle(7);
    return EXIT_SUCCESS;
}

void print_pascals_triangle(int n)
{
    if (n <= 0) {
        printf("N must be greater than 0\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        int value = 1;

        for (int j = 0; j <= i; j++) {
            printf("%4d", value);
            value = value * (i - j) / (j + 1);
        }

        printf("\n");
    }
}
