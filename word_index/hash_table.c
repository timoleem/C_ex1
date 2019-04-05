#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "array.h"

/*
Timo Leemans
10785612
*/

/*
This code creates a table and can insert/delete/lookup nodes inside 
the table. It furthermore hashes nodes with the same key values. I managed 
to get till hash_lookup but I was not sure if I had to do any more improving
in this code instead of in the main.c file to get through that check. 
*/


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

/*Initialise a node and append it to an array with initial capacity 1. 
and assign pointers to the node*/
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
    // Free node and its pointers 
    array_cleanup(n->value);
    free(n->key);
    free(n);
    return n;
}

/* Create the struct table and assign pointers to it. Returns NULL if failed.*/
struct table *table_init(unsigned long capacity, double max_load,
                            unsigned long (*hash_func)(unsigned char *)) {
    // Struct the table 
    struct table *table = calloc(1, sizeof(struct table));
    if (table == NULL) {
        fprintf(stderr, "Allocation error.\n");
        return NULL;
    }
    // First check if the calloc succeeded
    table->array = calloc(capacity, sizeof(struct node));
    if (table->array == NULL) {
        fprintf(stderr, "Allocation error.\n"); 
        return NULL;
    }
    // Add all necessary pointers to the table 
    table->capacity = capacity;
    table->load = 0;
    table->max_load = max_load;
    table->hash_func = hash_func;
    return table;
}

/* Double the size of the hash table by creating a pointer to a new
hash array and adding all nodes to the new array. In the end, disconnect and 
free the 'old' hash array.*/
int double_size(struct table *t) {

    if (t == NULL) {
        return 1;
    }
    // Create new array with twice the size
    struct node** new_array = calloc((t->capacity)* 2, sizeof(struct node));
    if (new_array == NULL) {
        return 1;
    }
    // For each index in the the table. 
    for (unsigned long index = 0; index < t->capacity; index++) {
        // Get first node of the array
        struct node* current = t->array[index];
        while(current != NULL) {
            // Formula for index is : hash(key) % table capacity (of new array)
            unsigned long index = t->hash_func((unsigned char *) 
                                  current->key) % (t->capacity*2);
            // ... add it to the new array with the same index value
            if (new_array[index] == NULL) {
                new_array[index] = current;
            }
            // if it already exists, then add it to the end of the list
            else {
                struct node* n = new_array[index];
                while (n->next != NULL) {
                    n = n->next;
                }
                n->next = current;
            }
            // Disconnect old node and continue with the next node 
            struct node* next = current->next;
            current->next = NULL;
            current = next;
        }
    }
    // Free old table with its arrays and ..
    free(t->array);
    t->array = new_array;
    // .. set the capacity to twice its former value
    t->capacity = t->capacity*2;
    return 0;
}  

/* Insert node with key / value to the table. Return 1 if failed. */
int table_insert(struct table *t, char *key, int value) {
    
    if (t == NULL && key == NULL) {
        return 1;
    }
    // Load factor = # of elements / # of buckets
    float load_factor = (float) t->load / (float) t->capacity;

    // Double allocation space if necessary
    if (load_factor > t->max_load) {
        double_size(t);
    }
    // Formula for index is : hash(key) % backing_array_length;
    unsigned long index = t->hash_func((unsigned char *) key) % t->capacity;
    // add node to the start if there is none at the specific index
    if (t->array[index] == NULL) {
        struct node *n = node_init(key, value);
        t->array[index] = n;
        t->load++;
        return 0;
    }
    // Else if exists, loop through nodes till you are at the end
    else {
        struct node* current = t->array[index];

        while (current != NULL) {
            // If the keys are the same, then add the key to end of the array
            if (!strcmp(current->key, key)) {
                array_append(current->value, value);
                t->load++;
                return 0;
            }
            // Else point the last node to the the newly initialised key-node
            else if (current->next == NULL) {
                struct node* n = node_init(key, value);
                current->next = n;
                t->load++;
                return 0;
            }
            current = current->next;
        }
    }
    return 1;
}

/* Look up the key in the table and return the value assigned to it. First
look up the index of the key, then retrieve the node in the hash array. If it 
fails, return NULL. */
struct array *table_lookup(struct table *t, char *key) {
    
    // puts("START LOOKUP \n");
    if (t == NULL || key == NULL) {
        fprintf(stderr, "Key or table does not exist! \n");
        return 1;
    }
    // Formula for index is : hash(key) % backing_array_length;
    unsigned long index = t->hash_func((unsigned char *) key) % t->capacity;

    // if (t->array[index+1] != NULL) {
    //     index++;
    // }

    if (t->array[index] != NULL) {
        // if it exists, search in the hash array for the node and its value.
        struct node* current = t->array[index];
        while (current) {
            if (!strcmp(current->key, key)) {
                return current->value;
            }
            current = current->next;
        }
    }
    return NULL;
}

/* Delete the node with key from the table. If succeeded, return 0, and if not, 
return 1*/
int table_delete(struct table *t, char *key) {
    
    if (t == NULL || key == NULL) {
        return 1;
    }
    // index = hash(key) % backing_array_length;
    unsigned long index = t->hash_func((unsigned char *) key) % t->capacity;
    
    // not sure if this is necessary
    if (t->array[index] != NULL) {
        // If the key index exists, find it in the array
        struct node* current = t->array[index];
        if (current != NULL) {

            if (!strcmp(current->key, key)) {
                // key == first node? Remove node and set next to 1st in array 
                t->load = t->load - array_size(current->value);
                t->array[index] = current->next;
                free_node(current);
                return 0;
            }
            // Else search in array till you find it and remove it
            while (current != NULL) {

                if (current->next == NULL) {
                    fprintf(stderr, "Couldn't find key\n");
                    return 1;
                }
                if (!strcmp(current->next->key, key)) {
                    struct node* remove = current->next;
                    current->next = remove->next;
                    t->load = t->load - array_size(remove->value);
                    free_node(remove);
                    return 0;
                }
                current = current->next;
            }
        }
    }
}

/* Clean the table and its arrays by index. If there are multiple nodes in 
the array, then clear every node as well. */
void table_cleanup(struct table *t) {
    
    // if table exists, no need to free anything
    if (t == NULL) {
        return;
    }
    // if table has no arrays, only free the table
    if (t->array == NULL) {
        free(t);
        return;
    }
    // if table contains arrays, free all nodes in all arrays along with array.
    for (unsigned long i = 0; i < t->capacity; i++) {
        if (t->array[i] != NULL) {
            struct node* current = t->array[i];
            while (current) {
                struct node* next = current->next;
                free_node(current);
                current = next;
            }
        }
    }
    // free the pointer to array and the table itself
    free(t->array);
    free(t);
    return;
}
