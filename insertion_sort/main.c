#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include <ctype.h>

#include "list.h"
#define BUF_SIZE 1024

// Script for insertion sort 
// Made by  
// Timo Leemans
// Student number : 10785612
// 20 / 02 / 2019

static char buf[BUF_SIZE];

struct config {
    // You can ignore these options until you implement the
    // extra command-line arguments.

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
    while ((c = getopt (argc, argv, "udiz")) != -1) {
        switch (c) {
            case 'u': cfg->unique_values = 1; break;
            case 'd': cfg->descending_order = 1; break;
            case 'i': cfg->insert_intermediate = 1; break;
            case 'z': cfg->zip_alternating = 1; break;
            default:
                      fprintf(stderr, "invalid option: -%c\n", optopt);
                      return 1;
        }
    }
    return 0;
}

// Display the entire list, node for node
void display_list(struct list* l) {

    struct node* last = list_head(l);
    while (last) {
        int num = list_node_value(last);
        printf("%d\n", num);
        last = list_next(last); 
    }
}

// Check if char is numeric. This will not succeed if you have for 
// example -4- because there is no problem that there are multiple 
// negatives. 
char is_numeric(char p[]) {

    for (int i = 0; i < (signed) strlen(p); i++) {
        if (p[i] != '-' && !isdigit(p[i])) {
            return 0;
        }
    }
    return 1;
}

// Update the sorted list in ascending order
struct list* ascending_list(struct list *l) {

    struct list *sl = list_init();
    struct node *last = list_head(l);
    while(last != NULL) {
        // if the sorted list is empty, add the last node of list to it
        if (list_head(sl) == NULL) {
            struct node *new = list_new_node(list_node_value(last));
            list_add_front(sl, new);
        }
        // if the first node is bigger, add the node to the front
        else if (list_node_value(last) < list_node_value(list_head(sl))) {
            struct node *new = list_new_node(list_node_value(last));
            list_add_front(sl, new);
        }
        // if the first node is smaller, go through the sorted list until it
        // finds a number that is bigger. Then add it before the bigger num
        else {
            struct node *c = list_head(sl);
            while (c != NULL) {
                if (list_next(c) == NULL) {
                    struct node *new = list_new_node(list_node_value(last));
                    if (list_node_value(last) < list_node_value(c)) {
                        list_insert_before(sl, new, c);
                    }
                    else {
                        list_insert_after(sl, new, c);                        
                    }
                    break;
                }
                else if (list_node_value(last) < list_node_value(c)) {
                    struct node *new = list_new_node(list_node_value(last));
                    list_insert_before(sl, new, c);
                    break;
                }
                c = list_next(c);   
            }
        }
        last = list_next(last);
    }    
    return sl;
}

// Check if there are multiple values in the list and if so then 
// delete them. 
struct list* list_unique(struct list *l) {
    
    struct list *unique = list_init();
    struct node *last = list_head(l); 

    while (last != NULL) {
        if (list_head(unique) == NULL) {
            struct node *new = list_new_node(list_node_value(last));
            list_add_front(unique, new);
        }
        else if (!list_node_present(unique, last)) {
            struct node *new = list_new_node(list_node_value(last));
            list_add_back(unique, new);
        }
        last = list_next(last);
    }
    return unique;
}

// Revert the sorted list such that it is descending instead of 
// ascending. 
struct list* revert_list(struct list *l) {

    struct list *reverted = list_init();
    struct node *last = list_head(l); 

    while (last != NULL) {
        if (list_head(reverted) == NULL) {
            struct node *new = list_new_node(list_node_value(last));
            list_add_front(reverted, new);
        }
        else {
            struct node *new = list_new_node(list_node_value(last));
            list_add_front(reverted, new);
        }
        last = list_next(last);
    }
    return reverted;
}

// Calculate the average between two numbers and take it as an int
int intermediate(struct node *n, struct node *m) {

    int n_val = list_node_value(n);
    int m_val = list_node_value(m);
    int val = (n_val + m_val) / 2;
    return val;
}

// Insert the intermediate value of two nodes inbetween them
// for LENGTH-1 of the list
struct list* intermediate_insert(struct list *l) {

    struct node *last = list_head(l); 
    int length = list_length(l);
    for (int i = 0; i < length-1; i++) {        
        int val = intermediate(last, list_next(last));
        struct node *new = list_new_node(val);
        list_insert_after(l, new, last);
        last = list_next(list_next(last));
    }
    return l;
}

struct list* zip_lists(struct list *l, struct list *ll) {

    int length = list_length(ll);
    struct node *nn = list_head(ll);
    struct node *n = list_head(l);

    for (int i = 0; i < length; i++) {
        list_insert_after(l, nn, n);
        n = list_next(list_next(n));
        nn = list_next(nn);
    } 
}

// Alternate zip. Was not able to finish it but managed to implement the 
// list get ith and list cut after. Really have 10 more minutes left so 
// I have to leave it like this unfortunately... 
struct list* alternate_zip(struct list *l) {

    struct list *ll = list_init();
    struct list *zip = list_init();

    int length = list_length(l);
    struct node *nn = list_get_ith(l, length/2);
    ll = list_cut_after(l, nn);
    zip = zip_lists(l, ll); 
    return ll;
}



// Main program. It takes arguments for the specific actions and the 
// arg values for a list which it can convert according to a specific case
int main(int argc, char *argv[]) {
    struct config cfg;
    if (parse_options(&cfg, argc, argv) != 0) {
        return 1;
    }

    // initialize the list
    struct list* l = list_init();

    // initialize a node necessary to update the list
    struct node* n; 
    int num;
    
    // while the user provides input, add to the list if it is a digit
    while (fgets(buf, BUF_SIZE, stdin)) {
        // skips spaces and new lines to take all numerics
        for (char *p = strtok(buf, " \n"); p; p = strtok(NULL, " \n")) {
            //if it is a numeric, add it to the back of the list
            if (is_numeric(p)) {
                num = atoi(p);
                n = list_new_node(num);
                list_add_back(l, n);            
            }
        }
    }
    // if there is no list or if there is only 1 item in the list then
    // display it and return 0.  
    if (list_head(l) == NULL || list_next(list_head(l)) == NULL) {
        display_list(l);
        list_cleanup(l);
        return 0;
    } 

    // struct the normal ascending list l
    struct list *sl = ascending_list(l);

    // struct the list with only unique values
    if ((signed) cfg.unique_values == 1) {
        sl = list_unique(sl);
    }
    // struct the list in descending order. a.k.a. revert the ascending list
    if ((signed) cfg.descending_order == 1) {
        sl = revert_list(sl);
    }
    // insert a intermediate value inbetween two nodes
    if ((signed) cfg.insert_intermediate == 1) {
        sl = intermediate_insert(sl);
    }
    // zip alternating. This does not completely work yet, short in time! 
    if ((signed) cfg.zip_alternating == 1) {
        sl = alternate_zip(sl);
    }

    // Display the sorted list and free both the lists
    display_list(sl);
    list_cleanup(l);
    list_cleanup(sl);

    return 0;
}
