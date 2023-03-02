#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    void *value;
} entry;


typedef struct {
    entry *entries;
    size_t size;
    size_t buffer_size;
} dict;

dict *dict_create();
void  dict_free(dict *d);
void  dict_reserve(dict *d, size_t new_size);
void *dict_add(dict *d, char *key, void *value);
void *dict_remove(dict *d, char *key);
void *dict_find(dict *d, char *key);

#endif