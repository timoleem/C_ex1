#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

struct stack {

    int data[STACK_SIZE];
    int size;
};

struct stack *stack_init() {
    struct stack *s = malloc(sizeof(struct stack));
    printf("stack init\n");
    s->size = 0;

    return s;
}

void stack_cleanup(struct stack *s) {

    printf("cleanup\n");
    free(s);
}

int stack_push(struct stack *s, int c) {

    if (s->size == STACK_SIZE -1) {
        printf("Error: Stack overflow\n");
        return 1;
    }

    printf("Push Element %d\n", c);
    s->data[s->size++] = c;

    return 0;
}

int stack_pop(struct stack *s) {

    if (s->size == -1) {
        printf("POP Stack is Empty");
    }
    else {
        printf("Pop Element: %d \n", s->data[s->size]);
        s->size--;
    }

    return 0;
}

int stack_peek(struct stack *s) {

    if (s->size == 0) {
        printf("PEEK Stack is Empty");
    }
    else {
        printf("Peek Element: %d \n", s->data[s->size]);
    return 0;
    }
}

int stack_empty(struct stack *s) {
    if (s->size == -1) {
        return 1;
    }
    else {
        return 0;
    }
}
