#ifndef FLEXIBLEARRAYMEMBER
#define FLEXIBLEARRAYMEMBER
#include <stddef.h>

typedef struct {
    size_t cap;
    size_t len;
    int arr[];
} FlexArr;

FlexArr *FlexArr_init(const size_t cap);
void FlexArr_deinit(FlexArr **fa);
int FlexArr_push(FlexArr **fa, int val);
void FlexArr_pop(FlexArr *fa);
int FlexArr_get(FlexArr *fa);
void FlexArr_println(const FlexArr *fa);

#endif
