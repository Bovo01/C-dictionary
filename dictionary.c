#include "dictionary.h"

dict *dict_create() {
    dict* d = malloc(sizeof(dict));
    d->size = 0;
    d->buffer_size = 2;
    d->entries = malloc(sizeof(entry) * d->buffer_size);
    return d;
}

void dict_free(dict *d) {
    for (int i = 0; i < d->size; i++) {
        free(d->entries[i].key);
    }
    free(d->entries);
    free(d);
}

void dict_reserve(dict *d, size_t new_size) {
    if (new_size <= d->buffer_size)
        return;
    entry *new_e = malloc(sizeof(entry) * new_size);
    memmove(new_e, d->entries, d->size * sizeof(entry));
    free(d->entries);
    d->entries = new_e;
    d->buffer_size = new_size;
}

static void __insertion_sort(dict *d, char *key, void *value) {
    // Complessità O(n)
    int i = 0;
    while (i < d->size && strcmp(d->entries[i].key, key) < 0) {
        i++;
    }
    // Sposto valori successivi
    memmove(d->entries + i + 1, d->entries + i, (d->size - i) * sizeof(entry));
    // Aggiungo chiave
    d->entries[i].key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(d->entries[i].key, key);
    d->entries[i].value = value;
    d->size++;
}

static int __index(dict *d, char *key) {
    // Binary search => O(log n)
    int l = 0, r = d->size - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        int compare = strcmp(d->entries[mid].key, key);
        if (compare == 0) {
            return mid;
        } else if (compare > 0) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

static entry *__find(dict *d, char *key) {
    int found = __index(d, key);
    if (found == -1)
        return NULL;
    return d->entries + found;
}

void *dict_add(dict *d, char *key, void *value) {
    entry *found = __find(d, key);
    if (found) {
        void *returned = found->value;
        found->value = value;
        return returned;
    }
    if (d->size == d->buffer_size)
        dict_reserve(d, d->buffer_size * 2);
    __insertion_sort(d, key, value);
    return NULL;
}

void *dict_find(dict *d, char *key) {
    int found = __index(d, key);
    if (found == -1)
        return NULL;
    return d->entries[found].value;
}

void *dict_remove(dict *d, char *key) {
    int index = __index(d, key);
    if (index == -1)
        return NULL;
    void *value = d->entries[index].value;
    free(d->entries[index].key);
    memmove(d->entries + index, d->entries + index + 1, sizeof(entry) * (d->size - index - 1));
    d->size--;
    return value;
}
