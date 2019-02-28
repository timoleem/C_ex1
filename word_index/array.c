#include <stdlib.h>

#include "array.h"

// Necessary structs and variables for array
struct array {

	int* values;
};

/* Initialise an array and return a pointer to it.
 * Return NULL on failure. */
struct array* array_init(unsigned long initial_capacity) {
	
	struct array *a = malloc(sizeof(int) * initial_capacity);
    if (a == NULL) {
        return NULL;
    }
    return a;
}

/* Cleanup array data structure. */
void array_cleanup(struct array* a) {

	free(a);
}

/* Return the element at the index position in the array.
 * Return -1 if the index is not a valid position in the array. */
int array_get(struct array *a, unsigned long index) {

	// if (index >  a->size) {
	// 	return -1;
	// }
	int element = a->values;
	return element;
}

/* Note: Although this operation might require the array to be resized and
 * copied, in order to make room for the added element, it is possible to do
 * this in such a way that the amortized complexity is still O(1).
 * Make sure your code is implemented in such a way to guarantee this. */

/* Add the element at the end of the array.
 * Return 0 if succesful, 1 otherwise. */
int array_append(struct array *a, int elem) {
    
	a->values = elem;
	return 0;
	// if (a->size++ >  a->capacity) {
 // 		a->capacity *= 2;
 // 		a->values = (int*) realloc(a, sizeof(int) * a->capacity);	
 // 		return 0;		
	// }    
	// return 1;
}

/* Return the number of elements in the array */
unsigned long array_size(struct array *a) {

	int size = sizeof(a)/sizeof(a[0]);
	return size;
}
