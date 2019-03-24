/*
Leo Schreuders
student ID 5742978
Datastructuren en algoritmen
Linked List interface.
Specialized for integers.
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/* Linked list data structure. */
struct list {
  struct node *head;
  struct node *tail;
};

/* List node structure. */
struct node {
  int value;
  struct node *next;
  struct node *previous;
};

/* Creates a new linked list and returns a pointer to it.
 * Returns NULL on failure. */
struct list *list_init(void) {
  struct list *l = malloc(sizeof(struct list));
  if (l == NULL) {
    fprintf(stderr, "List could not be initialized.\n");
    return NULL;
  }
  l->head = NULL;
  l->tail = NULL;
  return l;
}

/* Creates a new node that contains the number num and returns a pointer to it.
 * Returns NULL on failure. */
struct node *list_new_node(int num) {
  struct node *new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    fprintf(stderr, "Node could not be created.\n");
    return NULL;
  }
  new_node->value = num;
  new_node->next = NULL;
  new_node->previous = NULL;
  return new_node;
}

/* Returns the first node of the list L or NULL if list is empty. */
struct node *list_head(struct list *l) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return NULL;
  }
  struct node *head = l->head;
  if (head == NULL)
    return NULL;
  return l->head;
}

/* Returns a pointer to the node after node N or NULL if N is the last node in
 * the list. */
struct node *list_next(struct node *n) {
  if (n == NULL) {
    fprintf(stderr, "This is not a valid node\n");
    return NULL;
  }
  return n->next;
}

/* Inserts node N at the front of list L.
 * Returns 0 if N was succesfully inserted, 1 otherwise. */
int list_add_front(struct list *l, struct node *n) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return 1;
  }
  if (n == NULL) {
    fprintf(stderr, "This is not a valid node.\n");
    return 1;
  }
  if (list_node_present(l, n)) {
    fprintf(stderr, "Node already in list.\n");
    return 1;
  }
  if (list_head(l) == NULL) {
    l->head = n;
    l->tail = n;
    return 0;
  }
  n->next = l->head;
  l->head = n;
  n->next->previous = n;
  if (l->head == n) {
    return 0;
  }
  return 1;
}

/* Returns the last node of the list L or NULL if list is empty. */
struct node *list_tail(struct list *l) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return NULL;
  }
  return l->tail;
}

/* Returns a pointer to the node before node N in the list L, or returns NULL
 * if N is the first node in the list or if N is not in the list at all. */
struct node *list_prev(struct list *l, struct node *n) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return NULL;
  }
  if (n == NULL) {
    fprintf(stderr, "This is not a valid node.\n");
    return NULL;
  }
  if (!list_node_present(l, n)) {
    fprintf(stderr, "Node not in list.\n");
    return NULL;
  }
  if (l->head == n) {
    return NULL;
  }
  return n->previous;
}

/* Appends node N at the back of list L.
 * Returns 0 if N was succesfully appended, 1 otherwise. */
int list_add_back(struct list *l, struct node *n) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return 1;
  }
  if (n == NULL) {
    fprintf(stderr, "This is not a valid node.\n");
    return 1;
  }
  if (list_node_present(l, n)) {
    fprintf(stderr, "Node already in list.\n");
    return 1;
  }
  if (l->head == NULL) {
    l->head = n;
  }
  if (l->tail == NULL) {
    l->tail = n;
  } else {
    l->tail->next = n;
    n->previous = l->tail;
    l->tail = n;
  }
  if (l->tail == n) {
    return 0;
  }
  return 1;
}

/* Returns the value stored in the list node N, or 0 if N is the NULL
 * pointer. */
int list_node_value(struct node *n) {
  if (n == NULL) {
    return 0;
  }
  return n->value;
}

/* Unlink node N from list L. After unlinking, the list L contains no pointers
 * to the node N and N contains no pointers to nodes in L.
 * Returns 0 if N was succesfully unlinked from list L, or 1 otherwise */
int list_unlink_node(struct list *l, struct node *n) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return 1;
  }
  if (n == NULL) {
    fprintf(stderr, "This is not a valid node.\n");
    return 1;
  }
  if (!list_node_present(l, n)) {
    fprintf(stderr, "Node not in list.\n");
    return 1;
  }

  // If n is the only node:
  if ((l->head == n) && (l->tail == n)) {
    l->head = NULL;
    l->tail = NULL;
    n->next = NULL;
    n->previous = NULL;
  }
  // If n is the first node:
  else if (l->head == n) {
    l->head = n->next;
    n->next->previous = NULL;
    n->next = NULL;
    n->previous = NULL;
  }
  // If n is the last node:
  else if (l->tail == n) {
    l->tail = n->previous;
    l->tail->next = NULL;
    n->next = NULL;
    n->previous = NULL;
  } else {
    n->previous->next = n->next;
    n->next->previous = n->previous;
    n->next = NULL;
    n->previous = NULL;
  }

  return list_node_present(l, n);
}

/* Frees node N. */
void list_free_node(struct node *n) {
  if (n == NULL) {
    fprintf(stderr, "This is not a valid node.\n");
    return;
  }
  free(n);
}

/* Cleans up entire list L data structure.
 * Returns 0 if succesful, 1 otherwise. */
int list_cleanup(struct list *l) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return 1;
  }
  struct node *current_node = l->head;
  if (current_node == NULL) {
    free(l);
    return 0;
  }
  if (current_node->next == NULL) {
    free(current_node);
    free(l);
    return 0;
  } else {
    struct node *next_node = current_node->next;
    while (current_node->next != NULL) {
      next_node = current_node->next;
      free(current_node);
      current_node = next_node;
    }
    free(current_node);
    free(l);
    return 0;
  }
  return 1;
}

/* Returns 1 if node N is present in list L, 0 otherwise. */
int list_node_present(struct list *l, struct node *n) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return 0;
  }
  if (n == NULL) {
    fprintf(stderr, "This is not a valid node.\n");
    return 0;
  }
  struct node *current_node = list_head(l);
  if (current_node == NULL)
    return 0;
  while (current_node != NULL) {
    if (current_node == n) {
      return 1;
    }
    current_node = list_next(current_node);
  }
  return 0;
}

/* Inserts node N after node M in list L.
 * Fails if node M is not in the list L or if node N is already in list L.
 * Returns 0 if N was succesfully inserted, or 1 otherwise. */
int list_insert_after(struct list *l, struct node *n, struct node *m) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return 1;
  }
  if ((n == NULL) || (m == NULL)) {
    fprintf(stderr, "One of the nodes is invalid.\n");
    return 1;
  }
  if ((list_node_present(l, n) == 1) || (list_node_present(l, m) == 0)) {
    fprintf(stderr, "Node could not be inserted.\n");
    return 1;
  }
  if (l->tail == m) {
    list_add_back(l, n);
    return 0;
  }
  m->next->previous = n;
  n->next = m->next;
  n->previous = m;
  m->next = n;
  return 0;
}

/* Inserts node N before node M in list L.
 * Fails if node M is not in the list L or if node N is already in list L.
 * Returns 0 if N was succesfully inserted, or 1 otherwise. */
int list_insert_before(struct list *l, struct node *n, struct node *m) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return 1;
  }
  if ((n == NULL) || (m == NULL)) {
    fprintf(stderr, "One of the nodes is invalid.\n");
    return 1;
  }
  if ((list_node_present(l, n) == 1) || (list_node_present(l, m) == 0)) {
    fprintf(stderr, "Node could not be inserted.\n");
    return 1;
  }
  if (l->head == m) {
    list_add_front(l, n);
    return 0;
  }
  n->previous = m->previous;
  n->next = m->previous->next;
  m->previous = n;
  n->previous->next = n;

  return 0;
}

/* Returns the length of list L, or 0 if L is the NULL pointer */
int list_length(struct list *l) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return 0;
  }
  int counter = 0;
  struct node *current_node = l->head;
  while (current_node != NULL) {
    counter++;
    current_node = current_node->next;
  }
  return counter;
}

/* Returns a pointer to the i^th node of list L or NULL if there is no i^th
 * element in list L. */
struct node *list_get_ith(struct list *l, int i) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return NULL;
  }
  if (list_length(l) < i) {
    fprintf(stderr, "List is too short.\n");
    return NULL;
  }
  struct node *current_node = list_head(l);
  for (int j = 1; j < i; j++) {
    current_node = list_next(current_node);
  }
  return current_node;
}

/* Cuts list L into 2 lists, with node N being the last node in the first half
 * and all nodes after nodes N are added to the second half, preserving the
 * same order they were in in the original list.
 * Modifies list L to only contain the first half and creates a new list for
 * the second half. Returns a pointer to the second half if succesfully cut
 * and NULL otherwise. */
struct list *list_cut_after(struct list *l, struct node *n) {
  if (l == NULL) {
    fprintf(stderr, "This is not a valid list.\n");
    return NULL;
  }
  if (n == NULL) {
    fprintf(stderr, "This is not a valid node.\n");
    return NULL;
  }
  if (!list_node_present(l, n)) {
    fprintf(stderr, "Node not in list.\n");
    return NULL;
  }
  if (list_tail(l) == n) {
    fprintf(stderr, "List already ends at that node.\n");
    return NULL;
  }
  struct list *list_2 = list_init();
  list_2->tail = l->tail;
  l->tail = n;
  list_2->head = n->next;
  n->next = NULL;
  list_2->head->previous = NULL;
  return list_2;
}
