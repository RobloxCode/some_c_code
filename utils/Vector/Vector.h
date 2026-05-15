/*
 * vec.h — generic resizable array for C
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
 * All macros work on any type.  The underlying implementation is in
 * vec_raw_* functions that operate on (void **data, size_t *size,
 * size_t *cap, size_t elem_size) so you can also use it without macros.
 */

#ifndef VEC_H
#define VEC_H

#include <stddef.h>   /* size_t                  */
#include <stdlib.h>   /* malloc, realloc, free    */
#include <string.h>   /* memmove                 */
#include <assert.h>   /* assert                  */

/* -------------------------------------------------------------------------
 * Typed vector struct — declare a Vec(T) for any type T.
 *
 *   Vec(float) floats;
 *   Vec(const char *) strings;
 * ------------------------------------------------------------------------- */
#define Vec(T) struct { T *data; size_t size; size_t cap; }

/* -------------------------------------------------------------------------
 * Initial and minimum capacity.
 * The array never shrinks below VEC_MIN_CAP when you pop or remove elements
 * (automatic shrinking would hurt push/pop amortisation).
 * ------------------------------------------------------------------------- */
#define VEC_INIT_CAP  4
#define VEC_MIN_CAP   4
#define VEC_GROWTH    2   /* capacity multiplier on realloc */

/* =========================================================================
 * RAW (type-erased) helpers
 *
 * These are the real implementation.  The typed macros below call them.
 * You can use them directly if you want a truly opaque vector.
 * ========================================================================= */

/*
 * vec_raw_reserve — ensure at least `new_cap` slots are available.
 * Returns 1 on success, 0 on allocation failure.
 */
static inline int
vec_raw_reserve(void **data, size_t *cap, size_t new_cap, size_t elem_size)
{
    if (new_cap <= *cap) return 1;

    /* Round up to the next power of two >= new_cap (keeps capacity a power
     * of two which makes the growth pattern very predictable). */
    size_t c = (*cap == 0) ? VEC_INIT_CAP : *cap;
    while (c < new_cap) c *= VEC_GROWTH;

    void *block = realloc(*data, c * elem_size);
    if (!block) return 0;  /* caller should handle OOM */

    *data = block;
    *cap  = c;
    return 1;
}

/*
 * vec_raw_push — append one element (pointed to by `elem`) to the back.
 * Returns 1 on success, 0 on OOM.
 */
static inline int
vec_raw_push(void **data, size_t *size, size_t *cap,
             size_t elem_size, const void *elem)
{
    if (!vec_raw_reserve(data, cap, *size + 1, elem_size)) return 0;
    memcpy((char *)*data + (*size) * elem_size, elem, elem_size);
    (*size)++;
    return 1;
}

/*
 * vec_raw_insert — insert one element at index `i`, shifting tail right.
 * Returns 1 on success, 0 on OOM or bad index.
 */
static inline int
vec_raw_insert(void **data, size_t *size, size_t *cap,
               size_t elem_size, size_t i, const void *elem)
{
    if (i > *size) return 0;
    if (!vec_raw_reserve(data, cap, *size + 1, elem_size)) return 0;

    char *base = (char *)*data;
    memmove(base + (i + 1) * elem_size,
            base + i       * elem_size,
            (*size - i)    * elem_size);
    memcpy(base + i * elem_size, elem, elem_size);
    (*size)++;
    return 1;
}

/*
 * vec_raw_remove — remove element at index `i`, shifting tail left.
 * Returns 1 on success, 0 on bad index.
 */
static inline int
vec_raw_remove(void **data, size_t *size, size_t elem_size, size_t i)
{
    if (i >= *size) return 0;
    char *base = (char *)*data;
    memmove(base + i       * elem_size,
            base + (i + 1) * elem_size,
            (*size - i - 1) * elem_size);
    (*size)--;
    return 1;
}

/*
 * vec_raw_swap_remove — O(1) remove: swap element i with last, then pop.
 * Does NOT preserve order — use when order doesn't matter.
 */
static inline int
vec_raw_swap_remove(void *data, size_t *size, size_t elem_size, size_t i)
{
    if (i >= *size) return 0;
    if (i != *size - 1)
        memcpy((char *)data + i * elem_size,
               (char *)data + (*size - 1) * elem_size,
               elem_size);
    (*size)--;
    return 1;
}

/*
 * vec_raw_shrink — release excess memory, keeping exactly `size` slots.
 * Useful before serialising or passing to long-lived code.
 */
static inline int
vec_raw_shrink(void **data, size_t *cap, size_t size, size_t elem_size)
{
    size_t target = (size < VEC_MIN_CAP) ? VEC_MIN_CAP : size;
    if (target == *cap) return 1;

    void *block = realloc(*data, target * elem_size);
    if (!block && target > 0) return 0;  /* realloc to smaller shouldn't fail, but be safe */

    *data = block;
    *cap  = target;
    return 1;
}

/* =========================================================================
 * TYPED macro API
 *
 * All macros evaluate their first argument (the vector pointer) exactly once.
 * The value macros (vec_at, vec_front, vec_back) are lvalues — you can write:
 *
 *   vec_at(&v, 2) = 99;
 * ========================================================================= */

/* Initialise a Vec before first use. */
#define vec_init(v)  ((v)->data = NULL, (v)->size = 0, (v)->cap = 0)

/* Free backing memory and reset to zero state. */
#define vec_free(v)  (free((v)->data), vec_init(v))

/* Number of elements currently stored. */
#define vec_len(v)   ((v)->size)

/* Capacity (slots allocated). */
#define vec_cap(v)   ((v)->cap)

/* True if the vector has no elements. */
#define vec_empty(v) ((v)->size == 0)

/* Element access — assert-guarded, lvalue.
 * Returns a reference so you can do: vec_at(&v, 2) = 99; */
static inline void *
_vec_at_ptr(void *data, size_t size, size_t elem_size, size_t i)
{
    assert(i < size);
    return (char *)data + i * elem_size;
}
#define vec_at(v, i) \
    (*((__typeof__((v)->data[0]) *)_vec_at_ptr((v)->data, (v)->size, sizeof((v)->data[0]), (i))))
#define vec_front(v)    vec_at(v, 0)
#define vec_back(v)     vec_at(v, (v)->size - 1)

/* Append a value.  Returns 1 on success, 0 on OOM. */
#define vec_push(v, val) \
    __extension__({ \
        __typeof__((v)->data[0]) _tmp = (val); \
        vec_raw_push((void **)&(v)->data, &(v)->size, &(v)->cap, \
                     sizeof((v)->data[0]), &_tmp); \
    })

/* Remove and return the last element.  Undefined if empty — check first. */
#define vec_pop(v) \
    (assert(!vec_empty(v)), (v)->data[--(v)->size])

/* Insert `val` at position `i`.  Returns 1 on success. */
#define vec_insert(v, i, val) \
    __extension__({ \
        __typeof__((v)->data[0]) _tmp = (val); \
        vec_raw_insert((void **)&(v)->data, &(v)->size, &(v)->cap, \
                       sizeof((v)->data[0]), (i), &_tmp); \
    })

/* Order-preserving remove at index `i`.  Returns 1 on success. */
#define vec_remove(v, i) \
    vec_raw_remove((void **)&(v)->data, &(v)->size, sizeof((v)->data[0]), (i))

/* O(1) unordered remove at index `i`. */
#define vec_swap_remove(v, i) \
    vec_raw_swap_remove((v)->data, &(v)->size, sizeof((v)->data[0]), (i))

/* Pre-allocate capacity for at least `n` elements.  Returns 1 on success. */
#define vec_reserve(v, n) \
    vec_raw_reserve((void **)&(v)->data, &(v)->cap, (n), sizeof((v)->data[0]))

/* Release excess capacity — compact to current size. */
#define vec_shrink(v) \
    vec_raw_shrink((void **)&(v)->data, &(v)->cap, (v)->size, sizeof((v)->data[0]))

/* Remove all elements (keeps allocation). */
#define vec_clear(v)  ((v)->size = 0)

/* For-each loop.  `it` is a pointer to each element, type auto-deduced.
 *
 *   vec_foreach(&v, it) { printf("%d\n", *it); }
 */
#define vec_foreach(v, it) \
    for (__typeof__((v)->data) it = (v)->data; \
         it < (v)->data + (v)->size; \
         ++it)

#endif /* VEC_H */
