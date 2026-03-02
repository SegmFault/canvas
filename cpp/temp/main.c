#include "base.h"
#include <stdio.h>

int main()
{
    Area arena = area_init(1024 * 1024 * 64);

    size_t n  = 1024;
    int *arr = area_alloc(&arena, sizeof(int) * n);
    /* there will do some work on this array maybe render a pixel
     calculate some value and so on */
    for(int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
    /* work done */
    area_destroy(&arena);
    printf("Dynamic linking\n");
    return 0;
}
