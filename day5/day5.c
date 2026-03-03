#include <stdio.h>
#include <stdlib.h>
#include "../utils/ArrayList/ArrayListImp.h"

void print_pascal_triangle(int rows);

int main(void) {
    ArrayList *al = ArrayList_create(5);
    if (!al)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void print_pascal_triangle(int rows) {
    if (rows <= 0) {
        return;
    }
}
