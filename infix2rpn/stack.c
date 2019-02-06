#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

struct stack {

    int data[STACK_SIZE];
    int stack_top;
};

struct stack *stack_init() {
    struct stack *s = malloc(sizeof(struct stack));
    s->stack_top = -1;
    // Early exit with return alue 1 when stack is null pointer
    if (!s) {
        return NULL;
    }

    return s;
}

void stack_cleanup(struct stack *s) {

    free(s);
}

int stack_push(struct stack *s, int c) {

    if (s->stack_top == STACK_SIZE-1) {
        return 1;
    }
    else {
        s->stack_top++; 
        s->data[s->stack_top] = c;
        return 0;    
    }
}

int stack_pop(struct stack *s) {

    if (s->stack_top == -1) {
        return -1;
    }
    else {
        int pop_element = s->data[s->stack_top];
        s->stack_top--;
        return pop_element;
    }
}

int stack_peek(struct stack *s) {

    if (s->stack_top == -1) {
        return -1;
    }
    else {
        int pop_element = s->data[s->stack_top];
        return pop_element;
    }
}

int stack_empty(struct stack *s) {
    if (s->stack_top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}
