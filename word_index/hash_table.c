#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "array.h"

/* Struct for the table*/
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
 * pass all tests. However, the other options ares generally harder to code. */
struct node {
    // The string of characters that is the key for this node
    char *key;
    // A resizing array, containing the all the integer values for this key
    struct array *value;

    // Next pointer
    struct node *next;
};

struct node* node_init(char key, int value) {

    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    struct array *a = array_init(1);
    if (a == NULL) {
        return NULL;
    }
    n->value = a;
    return n;
}

/* Clear up node and its pointers. Return 1 if it failed. */
struct node *free_node(struct node* n) {

    if (n == NULL) {
        return 1;
    }
    free(n->value);
    free(n);
    return 0;
}

/* Create the struct table and assign pointers to it. Returns NULL if failed.*/
struct table *table_init(unsigned long capacity, double max_load,
                            unsigned long (*hash_func)(unsigned char *)) {
    struct table *table = calloc(1, sizeof(struct table));
    if (table == NULL) {
        return NULL;
    }
    table->capacity = capacity;
    table->load = 0;
    table->max_load = max_load;
    table->hash_func = hash_func;
    table->array = calloc(capacity, sizeof(struct node));
    if (table->array == NULL) {
        return NULL;
    }
    return table;
}

int double_size(struct table *t) {

    if (t == NULL) {
        return 1;
    }
    struct node* new_table = calloc((t->capacity)* 2, sizeof(struct node));
    if (new_table == NULL) {
        return 1;
    }
    for (unsigned long i = 0; i < t->capacity; i++) {

        // Get first node
        struct node* current = t->array[i];
        while(current != NULL) {

            unsigned long index = t->hash_func((unsigned char *) key) % t->capacity

            if (t->new_table[index] == NULL) {
                new_table[index] = current;
            }
            struct node* next = current->next;
            current->next = NULL;
            current = next;
        }
    }
}

/* Insert node with key / value to the table. Return 1 if failed. */
int table_insert(struct table *t, char *key, int value) {
    
    if (t == NULL && key == NULL) {
        return 1;
    }

    // if node exists, loop through nodes till you are at the end

    // else if node does not exist in hash table, add new node


}

struct array *table_lookup(struct table *t, char *key) {
    // ... SOME CODE MISSING HERE ...
}

int table_delete(struct table *t, char *key) {
    // ... SOME CODE MISSING HERE ...
}

void table_cleanup(struct table *t) {
    
    free(t->array);
    free(t);
}
