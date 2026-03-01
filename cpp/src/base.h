// base.h
#ifndef BASE_H_
#define BASE_H_

#include <stdlib.h>

// ---Declaration section---
typedef struct {
    uint8_t *buf;
    size_t capacity;
    size_t curr;
} Area;

Area area_init();
void* area_alloc(Area* s, size_t size);
void area_reset();

#endif //BASE_H_

// ---Implementation section---
#ifdef BASE_IMPLEMENTATION

Area area_init(size_t init_cap)
{
    Area pool = {
	.buf = malloc(init_cap),
	.capacity = init_cap,
	.curr = 0,
    };
    return pool;
}

void* area_alloc(Area* s, size_t size)
{
    if(s->curr+size  > s->capacity) {
	//exit
	;
    }
    s->buf += size;
    s->curr += size;
}
