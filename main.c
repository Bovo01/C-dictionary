#include <stdio.h>
#include "dictionary.h"

int main() {
    int int_size = sizeof(int);
    dict *d = dict_create();

    int *x = malloc(int_size);
    *x = 4;
    dict_add(d, "prova", x);
    int *y = malloc(int_size);
    *y = 10;
    dict_add(d, "prova", x);
    dict_add(d, "prova", y);
    dict_add(d, "nabo", x);
    int *z = malloc(int_size);
    *z = 15;
    dict_add(d, "sempre nabo", z);

    int *a = (int *) dict_remove(d, "prova");

    printf("a == y ? %d\n\n", a == y);

    for (int i = 0; i < d->size; i++) {
        printf("%s : %d\n", d->entries[i].key, *((int *) d->entries[i].value));
    }

    dict_free(d);
    free(x);
    free(y);
    free(z);
    return 0;
}
