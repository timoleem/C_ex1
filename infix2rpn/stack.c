#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <string.h>

struct stack {

    int data[STACK_SIZE];
    int stack_top;
    int push;
    int pop;
    int max;
    int max_dynamic;
};

struct stack *stack_init() {

    struct stack *s = malloc(sizeof(struct stack));
    s->stack_top = -1;
    s->push = 0;
    s->pop = 0;
    s->max = 0;
    s->max_dynamic = 0;

    if (!s) {
        return NULL;
    }
    return s;
}

void stack_cleanup(struct stack *s) {
    fprintf( stderr, "stats %d %d %d \n", s->push, s->pop, s->max);
    free(s);
}

/* Push operator to the stack if not the max size is exceeded AND 
   stack is not NULL */
int stack_push(struct stack *s, int c) {
    if (s == NULL) {
        return 1;
    }
    else if (s->stack_top == STACK_SIZE-1) {
        return 1;
    }
    else {
        s->stack_top++; 
        s->push++; 
        s->data[s->stack_top] = c;
        s->max_dynamic++;
        /* Every time a operator is added to the stacksize, check if it has
        exceeded the mac value of the stack size. */
        if (s->max < s->max_dynamic) {
            s->max = s->max_dynamic;
        }
        return 0;    
    }
}

/* Pop operator off the stack if stack is not empty AND 
   stack is not NULL */
int stack_pop(struct stack *s) {
    if (s == NULL) {
        return -1;
    }
    else if (s->stack_top == -1) {
        return -1;
    }  
    // Keep track of the dynamic size of the stack and pop operator
    else {
        int pop_operator = s->data[s->stack_top];
        s->stack_top--;
        s->pop++;
        s->max_dynamic--;
        return pop_operator;
    }
}

/* Peek operator from the stack if stack is not empty AND 
   stack is not NULL */
int stack_peek(struct stack *s) {
    if (s == NULL) {
        return -1;
    }
    else if (s->stack_top == -1) {
        return -1;
    }
    else {
        int pop_operator = s->data[s->stack_top];
        return pop_operator;
    }
}

/* Empty stack if stack is not empty AND stack is not NULL */
int stack_empty(struct stack *s) {

    if (s == NULL) {
        return -1;
    }
    else if (s->stack_top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}
