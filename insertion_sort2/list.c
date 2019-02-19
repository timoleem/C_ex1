#include "list.h"

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

struct list* list_init(void) {
    ;
}

struct node* list_new_node(int num) {
    ;
}

struct node* list_head(struct list* l) {
    ;
}

struct node* list_next(struct node* n) {
    ;
}

int list_add_front(struct list* l, struct node* n) {
    ;
}

struct node* list_tail(struct list* l) {
    ;
}

struct node* list_prev(struct list* l, struct node* n) {
    ;
}

int list_add_back(struct list* l, struct node* n) {
    ;
}

int list_node_value(struct node* n) {
    ;
}

int list_unlink_node(struct list* l, struct node* n) {
    ;
}

void list_free_node(struct node* n) {
    ;
}

int list_cleanup(struct list* l) {
    ;
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
