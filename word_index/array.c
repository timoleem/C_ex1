#include <stdlib.h>
#include "array.h"

/*
Timo Leemans
10785612
*/

/*
This file constructs an array that can get and append keys and values
inside the array. It multiplies its capacity every time the current size
exceeds the capacity of the array.*/

// Necessary structs and variables for array
struct array {

    unsigned long capacity;
    unsigned long size;
    int* data;
};

/* Initialise an array and return a pointer to it.
 * Return NULL on failure. */
struct array* array_init(unsigned long initial_capacity) {
    
    // initialise array and assign pointers to it.
    struct array *a = calloc(1, sizeof(struct array));
    if (a == NULL) {
        return NULL;
    }
    a->data = calloc(initial_capacity, sizeof(int));
    if (a->data == NULL) {
        free(a);
        return NULL;
    }
    a->size = 0;
    a->capacity = initial_capacity;
    return a;
}

/* Cleanup array data structure. */
void array_cleanup(struct array* a) {

    if (a == NULL) {
        return;
    }
    free(a->data);
    free(a);
}

/* Return the element at the index position in the array.
 * Return -1 if the index is not a valid position in the array. */
int array_get(struct array *a, unsigned long index) {

    if ((a == NULL) || (index >= a->size) || (a->data == NULL)) {
        return -1;
    }
    return a->data[index];
}

/* Add the element at the end of the array.
 * Return 0 if succesful, 1 otherwise. */
int array_append(struct array *a, int elem) {
    
    if (a == NULL) {
        return 1;
    }
    // if the capacity is exceeded, double the size of the array
    if (a->size >= a->capacity) { 
        a->data = (int*) realloc(a->data, sizeof(int) * 2 * a->capacity);
        if (a->data == NULL) {
            return 1;
        }
        a->capacity = 2 * a->capacity;
    }
    // add the element at the end of the array (at index of length array)
    a->data[array_size(a)] = elem;
    a->size++;
    return 0;
}

/* Return the number of elements in the array */
unsigned long array_size(struct array *a) {

    if (a == NULL) {
        return 0;
    }
    return a->size;
}
