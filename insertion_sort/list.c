#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* 
 * TODO: A lot of code missing here. You will need to add implementations for
 * all the functions described in list.h here.
 * 
 * Start by adding the definitions for the list and node structs. You may
 * implement any of the Linked List versions discussed in the lecture, which
 * have some different trade-offs for the functions you will need to write. 
 * 
 * Note: The function prototypes in list.h assume the most basic Singly Linked
 * List. If you build some other version, you may not need all of the function
 * arguments for all of the described functions. This will produce a warning,
 * which you can suppress by adding a simple if-statement to check the value
 * of the unused parameter.
 *
 * Also, do not forget to add any required includes at the top of your file.
 */

struct list {

	struct node* head;
	int count;
};

struct node {

	struct node* next;
	int val;
};

/* Creates a new linked list and returns a pointer to it.
 * Returns NULL on failure. */
struct list* list_init(void) {

	struct list *l = malloc(sizeof(struct list));
	if (l == NULL) {
		return NULL;
	}
	l->head = NULL;
	return l;
}

/* Creates a new node that contains the number num and returns a pointer to it.
 * Returns NULL on failure. */
struct node* list_new_node(int num) {

	struct node *n = malloc(sizeof(struct node));
	if (n == NULL) {
		return NULL;
	}
	n->val = num;
	n->next = NULL;	
	return n;
}

/* Returns the first node of the list L or NULL if list is empty. */
struct node* list_head(struct list* l) {
	
	if (!l) {
        return NULL;
    } 
    return l->head;
}

/* Returns a pointer to the node after node N or NULL if N is the last node in
 * the list. */
struct node* list_next(struct node* n) {

    if (!n->next) {
    	return NULL;
    }
    return n->next;
}

/* Inserts node N at the front of list L.
 * Returns 0 if N was succesfully inserted, 1 otherwise. */
int list_add_front(struct list* l, struct node* n) {

	struct node *last = l->head;
	l->head = n;
	n->next = last;
	if (!l->head) {
		return 1;
	}
	return 0;
}

/* Returns the last node of the list L or NULL if list is empty. */
struct node* list_tail(struct list* l) {

    if(!l) {
    	return NULL;
    }
    struct node *last = l->head; 
    while (last != NULL) 
    { 
        last = last->next; 
    } 
    return last;
}

/* Returns a pointer to the node before node N in the list L, or returns NULL
 * if N is the first node in the list or if N is not in the list at all. */
struct node* list_prev(struct list* l, struct node* n) {

    struct node *last = l->head; 
    int count = 0;
    while (last != n) 
    { 
        last = last->next; 
        count++;
    } 
    if (last == NULL || count <= 1) {
    	return NULL;
    }
    return last;
}

/* Appends node N at the back of list L.
 * Returns 0 if N was succesfully appended, 1 otherwise. */
int list_add_back(struct list* l, struct node* n) {
    // ;
    if(!l) {
    	return NULL;
    }
    struct node *last = l->head; 
    while (last->next != NULL) { 

        last = last->next; 
    } 
    last->next = n;
    if (!last->next) {
		return 1;
	}
    return 0;    
}

/* Returns the value stored in the list node N, or 0 if N is the NULL
 * pointer. */
int list_node_value(struct node* n) {

	if (n != NULL) {
		return n->val;
	}
	return 0;
}

/* Unlink node N from list L. After unlinking, the list L contains no pointers
 * to the node N and N contains no pointers to nodes in L.
 * Returns 0 if N was succesfully unlinked from list L, or 1 otherwise */
int list_unlink_node(struct list* l, struct node* n) {
    ;
}

/* Frees node N. */
void list_free_node(struct node* n) {
    free(n);
}

/* Cleans up entire list L data structure.
 * Returns 0 if succesful, 1 otherwise. */
int list_cleanup(struct list* l) {
    free(l);
}

int list_node_present(struct list* l, struct node* n) {
    ;
}

int list_insert_after(struct list* l, struct node* n, struct node* m) {
    ;
}

int list_insert_before(struct list* l, struct node* n, struct node* m) {
    ;
}

int list_length(struct list* l) {
    ;
}

struct node* list_get_ith(struct list* l, int i) {
    ;
}

struct list* list_cut_after(struct list* l, struct node* n) {
    ;
}
