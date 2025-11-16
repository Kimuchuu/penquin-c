#ifndef PENQUIN_TABLE_H
#define PENQUIN_TABLE_H

#include <stddef.h>

typedef struct {
    char *key;
    void *element;
} TableEntry;

typedef struct {
    int length;
    int capacity;
    TableEntry *entries;
    size_t element_size;
} Table;

void table_init(Table *table, size_t element_size);
void table_put(Table *table, char *key, void *value);
void *table_get(Table *table, char *key);

#endif
