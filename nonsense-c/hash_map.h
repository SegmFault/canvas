#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <stddef.h>
#include <stdbool.h>
#define HASHMAP_CAPACITY 16
typedef struct HashItem HashItem;
struct HashItem {
    HashItem *next;             /* linked list */
    char *key;
    int value;
};

typedef struct Hashmap {
    size_t size;                /* bucket size */
    HashItem *table[HASHMAP_CAPACITY]; /* this is a table[] the elements in array is (HashItem *) pointer which point to HashItem */
} Hashmap;

Hashmap *Hashmap_create();
void Hashmap_init(Hashmap *m);
Hashmap *Hashmap_put(Hashmap *m, const char *key, int value);
int *Hashmap_get(Hashmap *m, const char *key);
void Hashmap_destroy(Hashmap *m);
int Hashmap_hash(const char* key);
#endif


#ifdef HASH_MAP_IMPLEMENTATION
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int Hashmap_hash(const char* key) {
    /* hash function: hash(key) -> index */
    int code = 0;
    while (*key) {
        code += *key++;
    }
    return code;
}

void Hashmap_init(Hashmap *m) {
    assert(m);
    m->size = HASHMAP_CAPACITY;
    memset(m->table, 0, sizeof(m->table));
}

Hashmap *Hashmap_create() {
    Hashmap *map = calloc(1, sizeof(Hashmap)); /* void* calloc( size_t num, size_t size ) */
    assert(map);
    map->size = HASHMAP_CAPACITY;
    return map;
}

Hashmap *Hashmap_put(Hashmap *m, const char *key, int value) {
    assert(m && key);
    unsigned int index = Hashmap_hash(key) % m->size; /* calculate the key index */
    HashItem *curr = m->table[index]; /* check current bucket case */
    while(curr) {
        if(strcmp(curr->key, key) == 0) {
            curr->value = value;
            return m;
        }
        curr = curr->next;
    }
    HashItem *i = malloc(sizeof(HashItem));
    assert(i);
    i->value=value;
    i->key=strdup(key);
    i->next=m->table[index];
    m->table[index]=i;
    return m;
}

int *Hashmap_get(Hashmap *m, const char *key) {
    assert(m&&key);
    unsigned int index = Hashmap_hash(key) % m->size;
    HashItem *currNode = m->table[index];
    while (currNode) {
        if ( strcmp(key, currNode->key) == 0 ) {
            return &(currNode->value);
        }
        currNode=currNode->next;
    }
    return NULL;
}

void Hashmap_destroy(Hashmap *m) {
    assert(m);
    for (size_t i = 0; i < m->size; ++i) {
        HashItem *curr= m->table[i]; /* traverse the table[] */
        while (curr) {                /* table[index] is a HashItem element has attr next like a linked list*/
            HashItem *tmp = curr;
            curr= curr->next;
            free(tmp->key);
            free(tmp);
        }
        m->table[i]= NULL;
    }
}
#endif
