#ifndef FLEXIBLEARRAYMEMBER
#define FLEXIBLEARRAYMEMBER
#include <stddef.h>

typedef enum {
    FA_OK,
    FA_ERR_WRONG_PTR,
    FA_ERR_RANGE,
    FA_ERR_REALLOC,
} FA_status;

typedef struct {
    size_t cap;
    size_t len;
    int arr[];
} FlexArr;

FlexArr *FlexArr_init(const size_t cap);
FA_status FlexArr_deinit(FlexArr **fa);
FA_status FlexArr_push(FlexArr **fa, int val);
FA_status FlexArr_pop(FlexArr *fa);
FA_status FlexArr_get(const FlexArr *fa, const size_t i, int *out);
FA_status FlexArr_println(const FlexArr *fa);
size_t FlexArr_len(const FlexArr *fa);

#endif
