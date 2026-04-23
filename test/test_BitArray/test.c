#include "../../utils/BitArray/BitArrayImp.h"

int main()
{
    int bin = 12;
    print_bin((unsigned char)bin);
    set(&bin, 0);
    set(&bin, 7);
    print_bin((unsigned char)bin);
    clear(&bin, 2);
    print_bin((unsigned char)bin);
    return 0;
}
