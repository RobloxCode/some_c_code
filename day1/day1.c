/*
 * Write a program that prints some shapes
 * of any size using *
 */

#include <stddef.h>
#include <stdio.h>

void print_cube(
    const size_t width,
    const size_t height,
    const char symbol
);
void print_triangle(const size_t height, const char symbol);

int main(void) {
    const size_t SIZE_TEST = 6;
    print_cube(SIZE_TEST, SIZE_TEST, '0');
    print_triangle(SIZE_TEST, '\\');
    return 0;
}

void print_cube(
    const size_t width,
    const size_t height,
    const char symbol
) {
    for (size_t w = 0; w < width; ++w) {
        for (size_t h = 0; h < height; ++h) {
            printf("%c", symbol);
        }
        printf("\n");
    }
}

void print_triangle(const size_t height, const char symbol) {
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            if (j == i) {
                printf("%c", symbol);
            }
            printf(" ");
        }
        printf("\n");
    }
}

