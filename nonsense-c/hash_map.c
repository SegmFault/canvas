#include <stdlib.h>
#define HASHMAP_INITIAL_CAPACITY 16

typedef struct HashItem HashItem;
struct HashItem {
    HashItem *next;             /* mount next item if conflict */
    char *key;
    int value;
};

typedef struct Hashmap {
    size_t size;                /* current bucket size */
    HashItem *table[HASHMAP_INITIAL_CAPACITY]; /* this is a table[] the elements in array is pointer point to HashItem */
} Hashmap;


/* pass pointer version */
void Hashmap_init(Hashmap *m) {
    assert(m);                  /* assert m is not NULL */
    m->size = HASHMAP_INITIAL_CAPACITY;
    memset(m->table, 0, sizeof(m->table));
}


/* return pointer version */
Hashmap *Hashmap_create() {
    Hashmap *map = calloc(1, sizeof(Hashmap)); /* void* calloc( size_t num, size_t size ) */
    assert(map);
    map->size = HASHMAP_INITIAL_CAPACITY;
    return map;
}


Hashmap *Hashmap_put(Hashmap *m, char *key, int value) {
    assert(m && key);
    unsigned int index = hash(key) % m->size; /* calculate the key index */
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

Hashmap *Hashmap_get(Hashmap *m, char *key) {
}
int hash(char* key) {
    /* hash function: hash(key) -> index */
    key[hello]
}

int main() {
    Hashmap *map1 = malloc(sizeof(Hashmap));
    Hashmap_init(map1);

    Haspmap *map2 = Hashmap_create();

    return 0;
}
