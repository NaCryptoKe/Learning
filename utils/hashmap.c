#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

typedef struct Entry {
    void *key;
    void *value;
    struct Entry *next;
} Entry_t;

typedef struct {
    Entry_t **buckets;
    int size;
} HashMap;

unsigned int hash (void *key, int keySize);
HashMap *hashmap_create(int size);
void hashmap_insert(HashMap *map, void *key, int keySize, void *value);
void *hashmap_get (HashMap *map, void *key, int keySize);
void hashmap_free(HashMap *map);

int main(void) {
    HashMap *map = hashmap_create(1);
    hashmap_insert(map, "list", 4, "list");
    hashmap_insert(map, "good", 4, "good");
    hashmap_insert(map, "hell", 4, "hell");
    void *get = hashmap_get(map, "list", 4);
    printf("%s", (char*)get);    
    get = hashmap_get(map, "good", 4);
    printf("%s", (char*)get);    
    get = hashmap_get(map, "hell", 4);
    printf("%s", (char*)get);    
    hashmap_free(map);
}

unsigned int hash (void *key, int keySize) {
    unsigned char *bytes = (unsigned char*) key;
    unsigned int h = 5381;

    for (int i = 0; i < keySize; i++) {
        h = h * 33 + bytes[i];
    }

    return h;
}

HashMap *hashmap_create(int size) {
    HashMap *map = malloc(sizeof(HashMap));
    if (map == NULL) {
        write(2, "Memory allocation failed.\n", 26);
        return NULL;
    }

    map->buckets = malloc(sizeof(Entry_t *) * size);
    if (map->buckets == NULL) {
        write(2, "Memory allocation failed.\n", 26);
        return NULL;
    }
    
    for (int i = 0; i < size; i++ ) {
        map->buckets[i] = NULL;
    }

    map->size = size;
    return map;
}

void hashmap_insert(HashMap *map, void *key, int keySize, void *value) {
    int hash_index = ((int)hash(key, keySize)) % map->size;

    Entry_t *entry = malloc(sizeof(Entry_t));
    if (entry == NULL) {
        write(2, "Memory allocation failed.\n", 26);
        return;
    }
    entry->key = key;
    entry->value = value;
    entry->next = NULL;

    if (map->buckets[hash_index] == NULL) {
        map->buckets[hash_index] = entry;
    } else {
        Entry_t *current = map->buckets[hash_index];
        while (current != NULL) {
            if (memcmp(current->key, key, keySize) == 0) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        entry->next = map->buckets[hash_index];
        map->buckets[hash_index] = entry;
    }
}

void *hashmap_get (HashMap *map, void *key, int keySize) {
    int hash_index = ((int)hash(key, keySize)) % map->size;

    Entry_t *get = map->buckets[hash_index];

    while (get != NULL) {
        if (memcmp(key, get->key, keySize) == 0) {
            return (void *)get->value;
        }
        get = get->next;
    }
    return NULL;
}

void hashmap_free(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        Entry_t *hash_free = map->buckets[i];
        while (hash_free != NULL) {
            Entry_t *next = hash_free->next;
            free(hash_free);
            hash_free = next;
        }
    }
    free(map->buckets);
    free(map);
}
