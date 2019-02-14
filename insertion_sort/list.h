/* Linked List interface.
 * Specialized for integers. */

/* Linked list data structure. */
struct list;

/* List node structure. */
struct node;

/* Creates a new linked list and returns a pointer to it.
 * Returns NULL on failure. */
struct list* list_init(void);

/* Creates a new node that contains the number num and returns a pointer to it.
 * Returns NULL on failure. */
struct node* list_new_node(int num);

/* Returns the first node of the list L or NULL if list is empty. */
struct node* list_head(struct list* l);

/* Returns a pointer to the node after node N or NULL if N is the last node in
 * the list. */
struct node* list_next(struct node* n);

/* Inserts node N at the front of list L.
 * Returns 0 if N was succesfully inserted, 1 otherwise. */
int list_add_front(struct list* l, struct node* n);

/* Returns the last node of the list L or NULL if list is empty. */
struct node* list_tail(struct list* l);

/* Returns a pointer to the node before node N in the list L, or returns NULL
 * if N is the first node in the list or if N is not in the list at all. */
struct node* list_prev(struct list* l, struct node* n);

/* Appends node N at the back of list L.
 * Returns 0 if N was succesfully appended, 1 otherwise. */
int list_add_back(struct list* l, struct node* n);

/* Returns the value stored in the list node N, or 0 if N is the NULL
 * pointer. */
int list_node_value(struct node* n);

/* Unlink node N from list L. After unlinking, the list L contains no pointers
 * to the node N and N contains no pointers to nodes in L.
 * Returns 0 if N was succesfully unlinked from list L, or 1 otherwise */
int list_unlink_node(struct list* l, struct node* n);

/* Frees node N. */
void list_free_node(struct node* n);

/* Cleans up entire list L data structure.
 * Returns 0 if succesful, 1 otherwise. */
int list_cleanup(struct list* l);

/* Returns 1 if node N is present in list L, 0 otherwise. */
int list_node_present(struct list* l, struct node* n);

/* Inserts node N after node M in list L.
 * Fails if node M is not in the list L or if node N is already in list L.
 * Returns 0 if N was succesfully inserted, or 1 otherwise. */
int list_insert_after(struct list* l, struct node* n, struct node* m);

/* Inserts node N before node M in list L.
 * Fails if node M is not in the list L or if node N is already in list L.
 * Returns 0 if N was succesfully inserted, or 1 otherwise. */
int list_insert_before(struct list* l, struct node* n, struct node* m);

/* Returns the length of list L, or 0 if L is the NULL pointer */
int list_length(struct list* l);

/* Returns a pointer to the i^th node of list L or NULL if there is no i^th
 * element in list L. */
struct node* list_get_ith(struct list* l, int i);

/* Cuts list L into 2 lists, with node N being the last node in the first half
 * and all nodes after nodes N are added to the second half, preserving the
 * same order they were in in the original list.
 * Modifies list L to only contain the first half and creates a new list for
 * the second half. Returns a pointer to the second half if succesfully cut
 * and NULL otherwise. */
struct list* list_cut_after(struct list* l, struct node* n);

