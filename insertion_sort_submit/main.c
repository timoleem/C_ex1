/*
Leo Schreuders
student ID 5742978
Dastructuren en Algoritmen
This code take numbers as input and sorts them.
*/

#include "list.h"
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024

static char buf[BUF_SIZE];

struct config {

  // Set to 1 if -u is specified, 0 otherwise.
  int unique_values;

  // Set to 1 if -d is specified, 0 otherwise.
  int descending_order;

  // Set to 1 if -i is specified, 0 otherwise.
  int insert_intermediate;

  // Set to 1 if -z is specified, 0 otherwise.
  int zip_alternating;
};

int parse_options(struct config *cfg, int argc, char *argv[]) {
  memset(cfg, 0, sizeof(struct config));
  int c;
  while ((c = getopt(argc, argv, "udiz")) != -1) {
    switch (c) {
    case 'u':
      cfg->unique_values = 1;
      break;
    case 'd':
      cfg->descending_order = 1;
      break;
    case 'i':
      cfg->insert_intermediate = 1;
      break;
    case 'z':
      cfg->zip_alternating = 1;
      break;
    default:
      fprintf(stderr, "invalid option: -%c\n", optopt);
      return 1;
    }
  }
  return 0;
}
/*
This function comes from
https://rosettacode.org/wiki/Determine_if_a_string_is_numeric#C
and checks if a string is numeric, also accepting negative numbers.
*/
int isNumeric(const char *s) {
  if (s == NULL || *s == '\0' || isspace(*s))
    return 0;
  char *p;
  strtod(s, &p);
  return *p == '\0';
}

/*
Take in numbers, sort them in a list, and print them based on the command line
arguments.
*/
int main(int argc, char *argv[]) {
  struct config cfg;

  // This pointer is used to acces the struct config.
  struct config *cfg_ptr = &cfg;

  if (parse_options(&cfg, argc, argv) != 0) {
    return 1;
  }
  // Make a new list.
  struct list *sorted_list = list_init();

  // Process the input.
  while (fgets(buf, BUF_SIZE, stdin)) {

    // Split the input by whitespace. Found on:
    // https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c
    for (char *p = strtok(buf, " \n"); p; p = strtok(NULL, " \n")) {

      // Only accept (positive and negative) numbers.
      if (isNumeric(p)) {
        int value = atoi(p);

        // Make a new node from the input.
        struct node *new_node = list_new_node(value);

        int length = list_length(sorted_list);

        if (length == 0)
          list_add_front(sorted_list, new_node);
        else {
          // Iterate over the list length, back to front, to find a node with
          // a smaller value.
          for (int i = length; i > 0; i--) {

            struct node *compared_node = list_get_ith(sorted_list, i);
            int last_value = list_node_value(compared_node);

            // If a node with a smaller or equal value is found, place the
            // current node after it and end the loop.
            if (value >= last_value) {
              list_insert_after(sorted_list, new_node, compared_node);
              i = 0;
            }
          }
          if (!list_node_present(sorted_list, new_node)) {
            list_add_front(sorted_list, new_node);
          }
        }
      }
    }
  }
  int length = list_length(sorted_list);

  // Remove duplicate values.
  if (cfg_ptr->unique_values) {
    // For every jth node, check if j+1th node is the same,
    // and remove the latter if so.
    for (int j = 1; j < length; j++) {
      struct node *node_1 = list_get_ith(sorted_list, j);
      int value_1 = list_node_value(node_1);
      struct node *node_2 = list_get_ith(sorted_list, j + 1);
      int value_2 = list_node_value(node_2);
      while ((value_1 == value_2) && (j < length)) {
        list_unlink_node(sorted_list, node_2);
        list_free_node(node_2);
        length = list_length(sorted_list);
        if (j < length) {
          node_2 = list_get_ith(sorted_list, j + 1);
          value_2 = list_node_value(node_2);
        }
      }
    }
    // Length needs to be updated.
    length = list_length(sorted_list);
  }

  // Reverse the ascending list into a descending one.
  if (cfg_ptr->descending_order) {

    // Make a new list.
    struct list *descending_list = list_init();

    // Starting at the front, take every jth node from the
    // old list and add it to the back of the new list.
    for (int j = 1; j <= length; j++) {
      struct node *old_node = list_get_ith(sorted_list, j);
      int value = list_node_value(old_node);
      struct node *new_node = list_new_node(value);
      list_add_front(descending_list, new_node);
    }
    free(sorted_list);
    sorted_list = descending_list;
  }

  // Insert intermediate values;
  if (cfg_ptr->insert_intermediate) {
    // Starting at the back, for every jth and j-1th node,
    // calculate the intermediate value and insert a new node
    // with that value in between.
    for (int j = length; j > 1; j--) {
      struct node *node_1 = list_get_ith(sorted_list, j);
      struct node *node_2 = list_get_ith(sorted_list, j - 1);
      double value_1 = (double)list_node_value(node_1);
      double value_2 = (double)list_node_value(node_2);
      int value_intermediate = (int)ceil((value_1 + value_2) / 2);
      struct node *node_intermediate = list_new_node(value_intermediate);
      list_insert_before(sorted_list, node_intermediate, node_1);
    }
    // Length has to be updated now.
    length = list_length(sorted_list);
  }

  // Cut the list into two and print them alternatingly.
  if ((cfg_ptr->zip_alternating) && (length > 1)) {
    // Length of the first list.
    int length_1 = (int)ceil((double)length / 2);
    struct node *last_node = list_get_ith(sorted_list, length_1);
    struct list *list_2 = list_cut_after(sorted_list, last_node);
    // Length of the second list.
    int length_2 = list_length(list_2);

    for (int j = 1; j <= length_1; j++) {
      struct node *node_1 = list_get_ith(sorted_list, j);
      int value = list_node_value(node_1);
      printf("%d\n", value);
      // This check is needed because the second list might be shorter.
      if (j <= length_2) {
        struct node *node_2 = list_get_ith(list_2, j);
        int value2 = list_node_value(node_2);
        printf("%d\n", value2);
      }
    }
  }
  // Print the list normally.
  else {
    for (int j = 1; j <= length; j++) {
      struct node *current_node = list_get_ith(sorted_list, j);
      int value = list_node_value(current_node);
      printf("%d\n", value);
    }
  }
  list_cleanup(sorted_list);
  return 0;
}
