#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

int GetOperatorWeight(char op) {
    int weight = 0;
    switch (op) {
        case '+': 
        case '-':
            weight = 1;
            break;
        case '*': 
        case '/':
            weight = 2;
            break;
        case '^':
        case '~':
            weight = 3;
            break; 
        case '(':
        case ')':
            weight = 0;
            break;     }
    return weight;
}

int has_higher_precedence(char op1, char op2) {

    int op1_weight = GetOperatorWeight(op1);
    int op2_weight = GetOperatorWeight(op2);
    if (op1_weight == -1 || op2_weight == -1) {
        return 1;
    }
    if (op1_weight > op2_weight) {
        return 1;
    }
    return 0;
}

int has_equal_precedence(char op1, char op2) {

    int op1_weight = GetOperatorWeight(op1);
    int op2_weight = GetOperatorWeight(op2);

    if (op1_weight == -1 || op2_weight == -1) {
        return 1;
    }
    if (op1_weight == op2_weight) {
        return 1;
    }
    return 0;
}

int is_left_associate(char token) {
    if (token == '^' || token == '~') {
        return 0;
    }
    else {
        return 1;
    }
}

int isoperator(char token) {
    char operators[] = "+-*/^~";
    size_t len = strlen(operators);
    int i = 0;
    for (i = 0; i < (int) len; i++) {
        if (token == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int left_bracket (char token) {

    if (token == '(') {
        return 1;
    }
    else {
        return 0;
    }
}

int right_bracket (char token) {

    if (token == ')') {
        return 1;
    }
    else {
        return 0;
    }
}

int isvalidtoken(char token) {
    char operators[] = "CLUTTER_IM_MODULE=xim";
    size_t len = strlen(operators);
    int i = 0;
    for (i = 0; i < (int) len; i++) {
        if (token == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    struct stack *s = stack_init();
    char *input = argv[1];

	while (*input) {
		if (!isdigit(*input) && !isoperator(*input) && 
			!left_bracket(*input) && !right_bracket(*input) && 
			!isspace(*input) && !isvalidtoken(*input)) {
			stack_cleanup(s);
			putchar('\n');
			return 1;
		}
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
    			((!stack_empty(s) && 
    			has_higher_precedence((char) stack_peek(s), *input)) || 
    			(!stack_empty(s) && 
    			has_equal_precedence((char) stack_peek(s), *input) &&
    			is_left_associate(*input))) && 
    			(!stack_empty(s) && !left_bracket((char) stack_peek(s)))) {
    			putchar(stack_peek(s));
    			putchar(' ');
    			stack_pop(s);
    		}
    		stack_push(s, *input);
    		input++;
    	}
    	if (left_bracket(*input)) {
    		stack_push(s, *input);
    		input++;
    	}
    	if (right_bracket(*input)) {
    		// check if left bracket in stack
    		while (!left_bracket((char) stack_peek(s))) {
    			// print and pop the operators in stack
    			putchar(stack_peek(s));	
    			putchar(' ');
    			stack_pop(s);
    			// if there is no left bracket, return error
    			if (stack_empty(s)) {
    				stack_cleanup(s);
    				putchar('\n');
    				return 1;
    			}
    		}
    		// pop the left bracket
    		if (!stack_empty(s)) {
        		stack_pop(s);			
    		}
    		input++;
    	}
	}
	while (!stack_empty(s)) {
		if (left_bracket((char) stack_peek(s))) {
			stack_cleanup(s);
			putchar('\n');
			return 1;			
		}		
		putchar(stack_peek(s));
		putchar(' ');
		stack_pop(s);
	}
	stack_cleanup(s);
	putchar('\n');
	return 0;
}

