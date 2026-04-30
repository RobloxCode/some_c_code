#include <stdio.h>

#define PERM_DISPLAY_OWN_R   0x00
#define PERM_DISPLAY_OWN_W   0x01
#define PERM_DISPLAY_OWN_X   0x02
#define PERM_DISPLAY_GROUP_R 0x03
#define PERM_DISPLAY_GROUP_W 0x04
#define PERM_DISPLAY_GROUP_X 0x05
#define PERM_DISPLAY_OTHER_R 0x06
#define PERM_DISPLAY_OTHER_W 0x07
#define PERM_DISPLAY_OTHER_X 0x08

struct Permissions {
    unsigned int owner_r : 1;
    unsigned int owner_w : 1;
    unsigned int owner_x : 1;
    unsigned int group_r : 1;
    unsigned int group_w : 1;
    unsigned int group_x : 1;
    unsigned int other_r : 1;
    unsigned int other_w : 1;
    unsigned int other_x : 1;
}__attribute__((packed));

void Permissions_print(struct Permissions p);

int main(void)
{
    struct Permissions p = (struct Permissions){1,1,1,1,0,1,1,0,0};
    Permissions_print(p);
    printf("Owner can execute: %d\n", p.owner_x);
    return 0;
}

void Permissions_print(struct Permissions p)
{
    if (p.owner_r & PERM_DISPLAY_OWN_R)   printf("owner read\n");
    if (p.owner_w & PERM_DISPLAY_OWN_W)   printf("owner write\n");
    if (p.owner_x & PERM_DISPLAY_OWN_X)   printf("owner execute\n");

    if (p.group_r & PERM_DISPLAY_GROUP_R) printf("group read\n");
    if (p.group_w & PERM_DISPLAY_GROUP_W) printf("group write\n");
    if (p.group_x & PERM_DISPLAY_GROUP_X) printf("group execute\n");

    if (p.other_r & PERM_DISPLAY_OTHER_R) printf("other read\n");
    if (p.other_w & PERM_DISPLAY_OTHER_W) printf("other read\n");
    if (p.other_x & PERM_DISPLAY_OTHER_X) printf("other read\n");
}
