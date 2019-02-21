#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "array.h"

struct table {
    // The (simple) array used to index the table
    struct node **array;
    // The function used for computing the hash values in this table
    unsigned long (*hash_func)(unsigned char *);
    
    // Maximum load factor after which the table array should be resized
    double max_load;
    // Capacity of the array used to index the table
    unsigned long capacity;
    // Current number of elements stored in the table
    unsigned long load;
};

/* Note: This struct should be a *strong* hint to a specific type of hash table
 * You may implement other options, if you can build them in such a way they
 * pass all tests. However, the other options are generally harder to code. */
struct node {
    // The string of characters that is the key for this node
    char *key;
    // A resizing array, containing the all the integer values for this key
    struct array *value;

    // Next pointer
    struct node *next;
};

// ... SOME CODE MISSING HERE ...

struct table *table_init(unsigned long capacity, double max_load,
                            unsigned long (*hash_func)(unsigned char *)) {
    // ... SOME CODE MISSING HERE ...
}

int table_insert(struct table *t, char *key, int value) {
    // ... SOME CODE MISSING HERE ...
}

struct array *table_lookup(struct table *t, char *key) {
    // ... SOME CODE MISSING HERE ...
}

int table_delete(struct table *t, char *key) {
    // ... SOME CODE MISSING HERE ...
}

void table_cleanup(struct table *t) {
    // ... SOME CODE MISSING HERE ...
}
