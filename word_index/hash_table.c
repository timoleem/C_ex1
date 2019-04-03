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

struct node* node_init(char* key, int value) {

    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    struct array *a = array_init(1);
    if (a == NULL) {
        return NULL;
    }
    // Append value to array, if return value 1, free all and return NULL
    if (array_append(a, value) == 1) {
        free(n);
        free(a);
        return NULL;
    }
    n->value = a;
    int length = strlen(key);
    n->key = malloc(sizeof(char) * length + 1);
    if (n->key == NULL) {
        return NULL;
    }
    // strcpy(n->key, key);
    strncpy(n->key, key, strlen(key)+1);
    n->next = NULL;
    return n;
}

/* Clear up node and its pointers. Return 1 if it failed. */
struct node *free_node(struct node* n) {

    if (n == NULL) {
        return NULL;
    }
    array_cleanup(n->key);
    free(n->value);
    free(n);
    puts("Freed node");
    return n;
}

/* Create the struct table and assign pointers to it. Returns NULL if failed.*/
struct table *table_init(unsigned long capacity, double max_load,
                            unsigned long (*hash_func)(unsigned char *)) {
    struct table *table = calloc(1, sizeof(struct table));
    if (table == NULL) {
        fprintf(stderr, "Allocation error.\n");
        return NULL;
    }
    table->array = calloc(capacity, sizeof(struct node));
    if (table->array == NULL) {
        fprintf(stderr, "Allocation error.\n"); 
        return NULL;
    }
    table->capacity = capacity;
    table->load = 0;
    table->max_load = max_load;
    table->hash_func = hash_func;
    puts("Made table \n");
    return table;
}

int double_size(struct table *t) {

    if (t == NULL) {
        return 1;
    }
    struct node** new_array = calloc((t->capacity)* 2, sizeof(struct node));
    if (new_array == NULL) {
        return 1;
    }
    for (unsigned long i = 0; i < t->capacity; i++) {

        // Get first node
        struct node* current = t->array[i];
        while(current != NULL) {

            unsigned long index = t->hash_func((unsigned char *) current->key) % t->capacity;

            if (new_array[index] == NULL) {
                new_array[index] = current;
            }
            else {
                struct node* n = new_array[index];
                while (n->next != NULL) {
                    n = n->next;
                }
                n->next = current;
            }
            struct node* next = current->next;
            current->next = NULL;
            current = next;
        }
    }
    free(t->array);
    t->array = new_array;
    t->capacity = t->capacity * 2;
    return 0;
}  

/* Insert node with key / value to the table. Return 1 if failed. */
int table_insert(struct table *t, char *key, int value) {
    
    puts("Attempts insert");
    if (t == NULL && key == NULL) {
        return 1;
    }
    puts("1");
    // load factor = # of elements / # of buckets
    float load_factor = (float) t->load / (float) t->capacity;

    // double allocation space if necessary
    if (load_factor > t->max_load) {
        double_size(t);
    }
    puts("2");
    unsigned long index = t->hash_func((unsigned char *) key) % t->capacity;
    // if node does not exist in hash table, add new node
    if (t->array[index] == NULL) {
        struct node* n = node_init(key, value);
        t->array[index] = n;
        t->load++;
        puts("3");        
    }    
    // else if exists, loop through nodes till you are at the end
    else {
        puts("4");
        struct node* current = t->array[index];
        puts("5");
        while (current->next != NULL) {
            current = current->next;
        }
        struct node* n = node_init(key, value);
        current->next = n;
        t->load++;
    }
    puts("Inserted value");
    return 0;
}


struct array *table_lookup(struct table *t, char *key) {
    
    if (t == NULL && key == NULL) {
        fprintf(stderr, "No valid key or table \n");
        return 1;
    }

    unsigned long index = t->hash_func((unsigned char *) key) % t->capacity;

    if (t->array[index] != NULL) {

        struct node* current = t->array[index];

        while (current) {
            if (strcmp(current->key, key)) {
                return current->value;
            }
            current = current->next;
        }
    }
    return NULL;
}

int table_delete(struct table *t, char *key) {
    // ... SOME CODE MISSING HERE ...
}

/* Clean the table and its arrays by index. If there are multiple nodes in 
the array, then clear every node as well. */
void table_cleanup(struct table *t) {
    
    if (t == NULL) {
        return;
    }

    if (t->array == NULL) {
        free(t);
        return;
    }

    for (long unsigned i = 0; i < t->capacity; i++) {
        if (t->array[i]) {
            struct node* current = t->array[i];
            while (current) {
                struct node* next = current->next;
                free_node(current);
                current = next;
            }
        }
    }
    free(t->array);
    free(t);
    return;
}
