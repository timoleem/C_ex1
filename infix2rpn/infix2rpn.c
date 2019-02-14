#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

// Assign operator weight to the operators and return this value
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

// Check if the new operator has a higher precedence
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

// Check if both operators have an equal precedence
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

// Check if the new operator is left associative
int is_left_associate(char token) {
	// Return zero if it is either ^ or ~
    if (token == '^' || token == '~') {
        return 0;
    }
    else {
        return 1;
    }
}

// Check if the token is an operator or not
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

// Check if the token is a left bracket
int left_bracket (char token) {

    if (token == '(') {
        return 1;
    }
    else {
        return 0;
    }
}

// Check if the token is a right bracket
int right_bracket (char token) {

    if (token == ')') {
        return 1;
    }
    else {
        return 0;
    }
}

// This is an extra check that I had to implement to make it work
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

// Main code for RPN 
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    struct stack *s = stack_init();
    char *input = argv[1];

	while (*input) {
		// Check if there is a valid token. Else return 1
		if (!isdigit(*input) && !isoperator(*input) && 
			!left_bracket(*input) && !right_bracket(*input) && 
			!isspace(*input) && !isvalidtoken(*input)) {
			stack_cleanup(s);
			putchar('\n');
			return 1;
		}
		// Check if there is a space, if so increment input
		if (isspace(*input)) {
			input++;
		}
		// Check if there is a digit
    	if (isdigit(*input)) {
    		putchar(*input);  
    		input++;
    		// In case the digit is higher then 9
    		while (isdigit(*input)) {
    			putchar(*input);
    			input++;
	    	}   
    		putchar(' ');
    	}
    	// Check if there is a operator
    	if (isoperator(*input)) {
    		/* If stack is NOT empty AND the new operator has higher precedence
    		   OR (new operator has equal precedence AND is left associative) 
    		   AND the new operator is NOT a left bracket. Then pop operator 
    		   from the stack and add it to the output queue */
    		while (((!stack_empty(s) && 
    				has_higher_precedence((char) stack_peek(s), *input)) || 
    				(!stack_empty(s) && 
    				has_equal_precedence((char) stack_peek(s), *input) &&
    				is_left_associate(*input))) && 
    				(!stack_empty(s) && !left_bracket((char) stack_peek(s)))) {
    			putchar(stack_peek(s));
    			putchar(' ');
    			stack_pop(s);
    		}
    		// Else push operator to the stack.
    		stack_push(s, *input);
    		input++;
    	}
    	// Check if token is a left bracket
    	if (left_bracket(*input)) {
    		stack_push(s, *input);
    		input++;
    	}
    	// Check if token is a right bracket
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
    		// pop the left bracket (do not add it to the output queue)
    		if (!stack_empty(s)) {
        		stack_pop(s);			
    		}
    		input++;
    	}
	}
	// Add existing operators in the stack if there are any
	while (!stack_empty(s)) {
		// If there is a left bracket left, return error
		if (left_bracket((char) stack_peek(s))) {
			stack_cleanup(s);
			putchar('\n');
			return 1;			
		}		
		putchar(stack_peek(s));
		putchar(' ');
		stack_pop(s);
	}
	// Clean-up stack and return valid check
	stack_cleanup(s);
	putchar('\n');
	return 0;
}
