#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

size_t strlen(char * s) {
    char *p = s;
    for (; *p != '\0'; p++);
    return p - s;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    struct stack *s = stack_init();
    char *input = argv[1];
    printf("%d \n ", )
	while (*input) {
		// if ((*input >= 'A' && *input <= 'Z') || 
		// 	(*input >= 'a' && *input <= 'z')) {
		// 	return 1;
		// }
		if (isspace(*input)) {
			input++;
		}
    	if (isdigit(*input)) {
    		putchar(*input);    		
    		input++;
    		while (isdigit(*input)) {
    			putchar(*input);
    			input++;
    		}
    		putchar(' ');    		
    	}
    	if (isoperator(*input)) {
    		while (
    			((!stack_empty(s) 
    			&& has_higher_precedence((char) stack_peek(s), *input)) 
    			|| (!stack_empty(s) 
    			&& has_equal_precedence((char) stack_peek(s), *input))) 
    			&& (!stack_empty(s) && !left_bracket((char) stack_peek(s)))) {
    			putchar(stack_peek(s));
    			putchar(' ');
    			add_pop(s);
    			add_max(s, 0);
    			stack_pop(s);
    		}
    		add_push(s);
    		add_max(s, 1);
    		stack_push(s, *input);
    		max(s);
    	}
    	if (left_bracket(*input)) {
    		add_max(s, 1);
    		add_push(s);
    		stack_push(s, *input);
    		max(s);
    	}
    	if (right_bracket(*input)) {
    		// check if left bracket in stack
    		while (!left_bracket((char) stack_peek(s))) {
    			// print and pop the operators in stack
    			putchar(stack_peek(s));	
    			putchar(' ');
    			add_pop(s);
    			add_max(s, 0);
    			stack_pop(s);
    			// if there is no left bracket, return error
    			if (stack_empty(s)) {
    				printf("Error : Mismatched parentheses");
    				break;
    			}
    		}
    		// pop the left bracket
    		if (!stack_empty(s)) {
    			add_pop(s);
    			add_max(s, 0);
        		stack_pop(s);			
    		}
    	}
    	input++;
	}
	while (!stack_empty(s)) {
		putchar(stack_peek(s));
		putchar(' ');
		add_max(s, 0);
		add_pop(s);
		stack_pop(s);
	}

	stack_cleanup(s);
	return 0;
}