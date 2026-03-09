/* arena_allocator.h */
#ifndef ARENA_ALLOCATOR_
#define ARENA_ALLOCATOR_

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

#endif //ARENA_ALLOCATOR_

/* Implementation section */
#ifdef ARENA_ALLOCATOR_IMPLEMENTATION

#include <assert.h>
#include <stdio.h>


Area area_init(size_t capacity)
{
    assert(capacity > 0 && "Area capacity must be a positive number");
    Area s = {};
    s.data = malloc(capacity);
    if(!s.data){
        fprintf(stderr,"error: initilize failed\n");
        exit(1);
    }
    s.capacity = capacity;
    s.curr = 0;
    return s;
}


void *area_alloc(Area *a, size_t size)
{
    assert(a != NULL && "Area pointer cannot be NULL");
    assert(a->data != NULL && "Arena data is NULL.");

    /* alignment memory */
    size_t align = 8;
    uintptr_t current_ptr = (uintptr_t) &a->data[a->curr]; /* fetch current address */
    uintptr_t aligned_ptr = (current_ptr + (align - 1)) & ~(align - 1); /* align address to 8 */

    size_t new_curr = (size_t)(aligned_ptr - (uintptr_t)a->data); /* calculate new bias */

    if(new_curr + size > a->capacity) {
        fprintf(stderr,"error: allocated failed\n");
        exit(1);
    }

    a->curr = new_curr + size;
    return (void*)aligned_ptr;
}

void area_reset(Area *a)
{
    a->curr = 0;
}

void area_destroy(Area *a)
{
    free(a->data);
    a->data = NULL;             /* avoid suspend pointer */
    a->capacity = 0;
    a->curr = 0;
}

#endif
