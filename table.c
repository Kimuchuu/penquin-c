#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "table.h"

static int hash(char *key, int max) {
    // TODO: Add true hash function from online
    return *key % max;
}

void table_init(Table *table, size_t element_size) {
    table->entries = NULL;
    table->length = 0;
    table->capacity = 0;
	table->element_size = element_size;
}

void table_put(Table *table, char *key, void *value) {
    if (table->length + 1 > table->capacity) {
        // TODO we probably need to reposition everything since
        // hash function would return different value
        int capacity = table->capacity == 0 ? 8 : table->capacity * 2;
        TableEntry *mem = (TableEntry *)realloc(table->entries, capacity * table->element_size);
        if (mem == NULL) {
            fprintf(stderr, "Unable to allocate memory for table\n");
            exit(1);
        }

        // Zero out the newly allocated space
        memset(mem + table->capacity, 0, (capacity - table->capacity) * table->element_size);

        table->capacity = capacity;
        table->entries = mem;
    }

    // TODO: Handle length and collisison
    int i = hash(key, table->capacity);
    table->entries[i].key = key;
    table->entries[i].element = value;
}

void *table_get(Table *table, char *key) {
    if (key == NULL || table->capacity == 0) {
        return NULL;
    }
    int i = hash(key, table->capacity);
    TableEntry entry = table->entries[i];
    return entry.element;
}

// int main() {
//     Table tbl;
//     table_init(&tbl, sizeof(char *));
//     table_put(&tbl, "1", "Hello");
//     table_put(&tbl, "2", "World");
//     char *hmm = (char *)table_get(&tbl, "1");
//     printf("what's this: %s\n", hmm);
//     return 0;
// }
