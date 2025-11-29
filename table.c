#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "table.h"

static int hash(char *key, int max) {
	unsigned int len = strlen(key);
	unsigned int hash = 2166136261u;
	for (int i = 0; i < len; i++) {
		hash = hash * 16777619u;
		hash = hash ^ key[i];
	}
    return hash % max;
}

void table_init(Table *table) {
    table->entries = NULL;
    table->length = 0;
    table->capacity = 0;
}

void table_put(Table *table, char *key, void *value) {
    if (table->length + 1 > table->capacity) {
		if (table->capacity	> 0) {
			// TODO we probably need to reposition everything since
			// hash function would return different value
			fprintf(stderr, "Exceeded max table capacity. Full rebuild required.\n");
			exit(1);
		}
	  
        int capacity = table->capacity == 0 ? 8 : table->capacity * 2;
        TableEntry *mem = (TableEntry *)realloc(table->entries, capacity * sizeof(TableEntry));
        if (mem == NULL) {
            fprintf(stderr, "Unable to allocate memory for table\n");
            exit(1);
        }

        // Zero out the newly allocated space
        memset(mem + table->capacity, 0, (capacity - table->capacity) * sizeof(TableEntry));

        table->capacity = capacity;
        table->entries = mem;
    }

    int i = hash(key, table->capacity);
	while (table->entries[i].key != NULL && strcmp(key, table->entries[i].key) != 0) {
		i = (i + 1) % (table->capacity - 1);
	}

	if (table->entries[i].key == NULL) {
		table->length++;
	}
	
    table->entries[i].key = key;
    table->entries[i].element = value;
}

void *table_get(Table *table, char *key) {
    if (key == NULL || table->capacity == 0) {
        return NULL;
    }
    int i = hash(key, table->capacity);
	int start_i = i;
	while (table->entries[i].key == NULL || strcmp(table->entries[i].key, key) != 0) {
		i = (i + 1) % (table->capacity - 1);
		if (i == start_i) return NULL;
	}
    TableEntry entry = table->entries[i];
    return entry.element;
}

