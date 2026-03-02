#define BASE_IMPLEMENTATION
#include "base.h"
#include <stdio.h>

int main()
{
    Area a = area_init(1024);
    void *p1 = area_alloc(&a, 1);
    void *p2 = area_alloc(&a, 1);
    void *p3 = area_alloc(&a, 1);

    printf("p1: %p\n", p1);
    printf("p2: %p\n", p2);
    printf("p3: %p\n", p3);
    area_destroy(&a);
    return 0;
}
