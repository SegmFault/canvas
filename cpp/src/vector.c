#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **data;              
    size_t count; 
    size_t capacity;
    size_t elem_size;
}Vector;

Vector* create_vector(size_t init_capacity, size_t elem_size) {
    Vector *v = malloc(sizeof(Vector));
    if(v == NULL) 
        return NULL;
    v->count = 0;
    v->capacity = init_capacity > 0 ? init_capacity : 1;
    v->elem_size = elem_size;
    v->data = malloc(v->capacity * sizeof(void *));
    if(v->data == NULL) {
        free(v);
        printf("alloc failed");
        return NULL;
    }
    return v;
}

/* push: add data to vector */
void push(Vector* v, void *elem_ptr) {
    if(v == NULL || elem_ptr == NULL) {
        printf("error: nullptr\n");
        return;
    }
    if(v->count >= v->capacity) {
        size_t new_capacity = v->capacity * 2;
        void **new_data = realloc(v->data, new_capacity * sizeof(void *) );
        if(new_data == NULL) {
            printf("alloc failed");
            return;
        }
    v->capacity = new_capacity;
    v->data = new_data;
    }
    
    void *new_mem = malloc(sizeof(v->elem_size));
    if(!new_mem)
        return;
    memcpy(new_mem, elem_ptr, v->elem_size);
    v->data[v->count++] = new_mem;
}

void* get(Vector *v, size_t index) {
    if(v == NULL)
        return NULL;
    if(index < 0 || index > v->count - 1)
        return 0;
    return v->data[index];
}
