/* vec_example.c — compile with: cc -o vec_example vec_example.c */
#include "../../utils/Vector/Vector.h"

#include <stdio.h>

int main(void) {
    /* --- basic int vector ------------------------------------------------ */
    Vec(int) v;
    vec_init(&v);

    for (int i = 0; i < 10; i++) {
        vec_push(&v, i * i); /* 0 1 4 9 16 25 36 49 64 81 */
    }

    printf("len=%zu  cap=%zu\n", vec_len(&v), vec_cap(&v));

    /* lvalue access */
    vec_at(&v, 0) = 999;

    /* iterate */
    vec_foreach(&v, it) printf("%d ", *it);
    putchar('\n');

    /* insert & remove */
    vec_insert(&v, 2, -1); /* insert -1 at index 2        */
    vec_remove(&v, 0);     /* remove index 0 (was 999)    */

    printf("after insert+remove: len=%zu\n", vec_len(&v));

    /* pop until empty */
    while (!vec_empty(&v)) {
        printf("pop: %d\n", vec_pop(&v));
    }

    vec_free(&v);

    /* --- string pointer vector ------------------------------------------- */
    Vec(const char *) words;
    vec_init(&words);

    vec_push(&words, "hello");
    vec_push(&words, "world");
    vec_push(&words, "from");
    vec_push(&words, "vec.h");

    vec_foreach(&words, w) printf("%s ", *w);
    putchar('\n');

    vec_free(&words);

    /* --- reserve up front (avoid reallocs in tight loop) ----------------- */
    Vec(double) samples;
    vec_init(&samples);
    vec_reserve(&samples, 1000);

    for (int i = 0; i < 1000; i++) {
        vec_push(&samples, i * 0.001);
    }

    vec_shrink(&samples); /* release excess capacity */
    printf("samples: len=%zu cap=%zu\n", vec_len(&samples), vec_cap(&samples));

    vec_free(&samples);
    return 0;
}
