#include "../../utils/BitArray/BitArrayImp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define do_test_BitArr      1
#define do_test_render_text 1
#define test 1

#if test
#define FLAG_BOLD       (1 << 0)
#define FLAG_ITALIC     (1 << 1)
#define FLAG_UNDERLINE  (1 << 2)
#define FLAG_STRIKEOUT  (1 << 3)
#endif

void render_text(const char *text, unsigned int flags);
void test_render_text(void);
int test_BitArr(void);

int main(void)
{

#if do_test_BitArr
    printf("BitArr test\n\n");
    test_BitArr();
#endif

#if do_test_render_text
    printf("render text test\n\n");
    test_render_text();
#endif

}

void render_text(const char *text, unsigned int flags)
{
    if (flags & FLAG_BOLD)      printf("bold\n");
    if (flags & FLAG_ITALIC)    printf("italic\n");
    if (flags & FLAG_UNDERLINE) printf("underline\n");

    printf("-> %s\n", text);
}

void test_render_text(void)
{
    render_text("Hello", FLAG_BOLD | FLAG_ITALIC | FLAG_UNDERLINE);
}

int test_BitArr(void)
{
    struct u8_BitArr bitArr = {0};
    if (u8_BitArr_print(&bitArr) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_set(&bitArr, 0) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_set(&bitArr, 1) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_set(&bitArr, 7) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_print(&bitArr) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_clear(&bitArr, 0) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_print(&bitArr) != 0)
        return EXIT_FAILURE;

    int bit = 0;
    for (int i = 0; i < 8; ++i) {
        if (u8_BitArr_get(&bitArr, i, &bit) != 0)
            return EXIT_FAILURE;

        printf("bit %d: %d\n", i, bit);
    }

    return EXIT_SUCCESS;
}
