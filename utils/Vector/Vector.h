/*
 * Vector.h — generic resizable array for C
 *
 * Usage (type-safe via macros):
 *
 *   Vec(int) v;
 *   vec_init(&v);
 *   vec_push(&v, 42);
 *   vec_push(&v, 99);
 *   printf("%d\n", vec_at(&v, 0));   // 42
 *   printf("%d\n", v.data[1]);       // 99 — direct access is fine too
 *   vec_free(&v);
 *
 * Compile Vector.c alongside your project.  All macros work on any type.
 */

#ifndef VEC_H
#define VEC_H

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------
 * Typed vector struct — declare a Vec(T) for any type T.
 *
 *   Vec(float) floats;
 *   Vec(const char *) strings;
 * ------------------------------------------------------------------------- */
#define Vec(T)                                                                 \
    struct {                                                                   \
        T *data;                                                               \
        size_t size;                                                           \
        size_t cap;                                                            \
    }

/* -------------------------------------------------------------------------
 * Tunables
 * ------------------------------------------------------------------------- */
#define VEC_INIT_CAP 4
#define VEC_MIN_CAP  4
#define VEC_GROWTH   2 /* capacity multiplier on realloc */

/* =========================================================================
 * RAW (type-erased) API — implemented in vec.c
 *
 * You can call these directly if you want a truly opaque vector.
 * The typed macros below are thin wrappers around them.
 * ========================================================================= */

/* Ensure at least `new_cap` slots are available.  Returns 1/0. */
int vec_raw_reserve(void **data, size_t *cap, size_t new_cap, size_t elem_size);

/* Append element pointed to by `elem`.  Returns 1/0. */
int vec_raw_push(void **data, size_t *size, size_t *cap, size_t elem_size,
                 const void *elem);

/* Insert element at index `i`, shifting tail right.  Returns 1/0. */
int vec_raw_insert(void **data, size_t *size, size_t *cap, size_t elem_size,
                   size_t i, const void *elem);

/* Remove element at index `i`, shifting tail left.  Returns 1/0. */
int vec_raw_remove(void **data, size_t *size, size_t elem_size, size_t i);

/* O(1) unordered remove: swap with last then shrink size.  Returns 1/0. */
int vec_raw_swap_remove(void *data, size_t *size, size_t elem_size, size_t i);

/* Bounds-checked element pointer (used by vec_at).  Asserts on bad index. */
void *vec_raw_at(void *data, size_t size, size_t elem_size, size_t i);

/* Release excess capacity down to current size.  Returns 1/0. */
int vec_raw_shrink(void **data, size_t *cap, size_t size, size_t elem_size);

/* =========================================================================
 * TYPED macro API
 * ========================================================================= */

/* Initialise a Vec before first use. */
#define vec_init(v) ((v)->data = NULL, (v)->size = 0, (v)->cap = 0)

/* Free backing memory and reset to zero state. */
#define vec_free(v) (free((v)->data), vec_init(v))

/* Queries. */
#define vec_len(v)   ((v)->size)
#define vec_cap(v)   ((v)->cap)
#define vec_empty(v) ((v)->size == 0)

/* Bounds-checked element access — lvalue, so vec_at(&v, i) = x works. */
#define vec_at(v, i)                                                           \
    (*((__typeof__((v)->data[0]) *)vec_raw_at((v)->data, (v)->size,            \
                                              sizeof((v)->data[0]), (i))))
#define vec_front(v) vec_at(v, 0)
#define vec_back(v)  vec_at(v, (v)->size - 1)

/* Append a value.  Returns 1 on success, 0 on OOM. */
#define vec_push(v, val)                                                       \
    __extension__({                                                            \
        __typeof__((v)->data[0]) _tmp = (val);                                 \
        vec_raw_push((void **)&(v)->data, &(v)->size, &(v)->cap,               \
                     sizeof((v)->data[0]), &_tmp);                             \
    })

/* Remove and return the last element.  Undefined behaviour if empty. */
#define vec_pop(v) (assert(!vec_empty(v)), (v)->data[--(v)->size])

/* Insert `val` at position `i`.  Returns 1 on success. */
#define vec_insert(v, i, val)                                                  \
    __extension__({                                                            \
        __typeof__((v)->data[0]) _tmp = (val);                                 \
        vec_raw_insert((void **)&(v)->data, &(v)->size, &(v)->cap,             \
                       sizeof((v)->data[0]), (i), &_tmp);                      \
    })

/* Order-preserving remove at index `i`.  Returns 1 on success. */
#define vec_remove(v, i)                                                       \
    vec_raw_remove((void **)&(v)->data, &(v)->size, sizeof((v)->data[0]), (i))

/* O(1) unordered remove at index `i`. */
#define vec_swap_remove(v, i)                                                  \
    vec_raw_swap_remove((v)->data, &(v)->size, sizeof((v)->data[0]), (i))

/* Pre-allocate capacity for at least `n` elements.  Returns 1 on success. */
#define vec_reserve(v, n)                                                      \
    vec_raw_reserve((void **)&(v)->data, &(v)->cap, (n), sizeof((v)->data[0]))

/* Release excess capacity — compact to current size. */
#define vec_shrink(v)                                                          \
    vec_raw_shrink((void **)&(v)->data, &(v)->cap, (v)->size,                  \
                   sizeof((v)->data[0]))

/* Remove all elements (keeps allocation). */
#define vec_clear(v) ((v)->size = 0)

/* For-each loop — `it` is a pointer to each element, type auto-deduced.
 *
 *   vec_foreach(&v, it) { printf("%d\n", *it); }
 */
#define vec_foreach(v, it)                                                     \
    for (__typeof__((v)->data) it = (v)->data; it < (v)->data + (v)->size; ++it)

#endif /* VEC_H */
