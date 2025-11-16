#ifndef PENQUIN_LIST_H
#define PENQUIN_LIST_H

#define LIST_GET(type, list, index) (((type *) (list)->elements)[index])

#include <stddef.h>

typedef struct {
    int length;
    int capacity;
    size_t element_size;
    void *elements;
} List;

List *list_init(List *list, size_t element_size);
void list_add(List *list, void *element);

#endif
