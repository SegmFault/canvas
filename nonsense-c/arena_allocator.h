#ifndef ARENA_ALLOCATOR_
#define ARENA_ALLOCATOR_

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#define REGION_DEFAULT_CAPACITY (64 * 1024)

/* Declaration section */
typedef struct Region Region;
struct Region {
    Region *next;
    size_t cap;
    size_t cur;                 /* use uintptr_t guarantee data start align */
    uintptr_t data[];           /* flexible array member */
};
/**
 *  if we use uint8_t data[]：uint8_t only need one byte aligned
 *  compiler maybe 紧贴着上一个成员放它。如果前面的成员加起来是 13 字节，data就会从第 14 个字节开始.
 *  uintptr_t data[]：uintptr_t 在 64 位系统上要求 8 字节对齐
 */

typedef struct Arena {
    Region *beg;
    Region *end;
} Arena;

Arena *Arena_create();
void *Arena_alloc(Arena *a, size_t size);
void Arena_reset(Arena *a);
void Arena_destroy(Arena *a);

#endif //ARENA_ALLOCATOR_


/* Implementation section */
#ifdef ARENA_ALLOCATOR_IMPLEMENTATION
#include <assert.h>


static Region *Region_create(size_t size)
{
    Region *rgn = (Region *)malloc(sizeof(Region) + size);
    if(!rgn)  return NULL;
    rgn->capacity = size;
    rgn->curr = 0;
    rgn->next = NULL;
    return rgn;
}

Arena *arena_create() {
    Arena *a = malloc(sizeof(Arena));
    if (!a)  return NULL;
    Region *fir_rgn = Region_create(REGION_DEFAULT_CAPACITY);
    if (!fir_rgn) {
        free(a);
        return NULL;
    }
    a->begin = fir_rgn
    a->end = fir_rgn;
    return a;
}


void *arena_alloc(Arena *a, size_t size, size_t aln)
{
    assert(a != NULL && "Arena pointer cannot be NULL");
    assert(a->begin != NULL && a->end != NULL && "Region is NULL.");
    assert(aln>0 && (aln & (aln-1)) == 0 && "align number should be a power of two");
/* Region r space occupancy status
 * r->cap = REGION_DEFAULT_CAPACITY
 * r->cur current position in Region r
 * _________________________
 * |                       |
 * |_______________________|
 *            ^
 *          r->cur
 *          if current position isn't a multipule of align
 *          we need aligned the addr;
 **/

    Region *r = a->end;
    /* uintptr_t addr = (uintptr_t)&r->data[r->cur];  */
    uintptr_t addr = (uintptr_t)r->data + r->cur;
    uintptr_t aln_addr = (addr + aln - 1) & ~((uintptr_t)aln - 1);
    size_t aln_cur = (size_t)(aln_addr - (uintptr_t)r->data);
    /* can hold */
    if (aln_cur + size <= r->cap) {
        r->cur = aln_cur + size;
        return (void *)aln_addr;
    }
    /* else allocate a new region */
    size_t next_cap = REGION_DEFAULT_CAPACITY;
    if (next_cap > cap)
        next_cap = aln +size;
    Region *n = Region_create(next_cap);
    assert(n != NULL && "allocate failed");
    r->next = n;
    a->end = n;

    uintptr_t addr = (uintptr_t)n->data;
    n->cur += size;
    return (void *)addr;
}

void arena_reset(Arena *a) {
    Region *cur_rgn = a->begin;
    while(cur_rgn != NULL) {
        cur_rgn->cur = 0;
        cur_rgn = cur_rgn->next;
    }
    a->end = a->begin;
}

void arena_destroy(Arena *a) {
    Region *cur_rgn = a->begin;
    while (cur_rgn != NULL) {
        Region *tmp = cur_rgn;
        cur_rgn = cur_rgn->next;
        free(tmp);
    }
    free(a);
}

#endif //ARENA_ALLOCATOR_IMPLEMENTATION_
