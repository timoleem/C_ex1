#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "stack.h"

// ... SOME CODE MISSING HERE ...

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    struct stack *s = stack_init();
    struct stack *o = stack_init();
    char *input = argv[1];
    int len = strlen(input);
    int i = 0;

    for (i=0; i<len; i++) {
    	if (isdigit(input[i])) {
    		stack_push(s, input[i]);
    	}
    	else {
    		printf("%d ", GetOperatorWeight(input[i]));
    		if (stack_empty(o)) {
    			stack_push(o, input[i]);
    		}
    	}
    }

    for (i = size_stack(s); i >= 0; i--) {
    	printf("%c ", stack_peek(s)); 
    	stack_pop(s);	
	}

    // printf("stats \n");

    return 0;
}

