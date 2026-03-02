// base.h
#include <stdlib.h>
#include <stdint.h>

/* Declaration section */
typedef struct {
    uint8_t *data;
    size_t capacity;
    size_t curr;
} Area;

Area area_init(size_t capacity);
void *area_alloc(Area *a, size_t size);
void area_reset(Area *a);
void area_destroy(Area *a);
