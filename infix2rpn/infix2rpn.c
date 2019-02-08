#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "stack.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s \"infix_expr\"\n", argv[0]);
        return 1;
    }

    struct stack *s = stack_init();
    char *input = argv[1];

	while (*input) {
		if (isspace(*input)) {
			input++;
		}
    	if (isdigit(*input)) {
    		putchar(*input);
    	}
    	if (isoperator(*input)) {

    		if (!stack_empty(s)) {
    			stack_push(s, *input);
    		}
    		else if (has_higher_precedence((char) stack_peek(s), *input)) {
    			stack_push(s, *input);
    		}
    		else if (has_equal_precedence((char) stack_peek(s), *input)) {
    			stack_push(s, *input);
    		}
    		else if (no_left_bracket(stack_peek(s))) {
    			stack_push(s, *input);
    		}
    		putchar(stack_peek(s));

    		// while ((!stack_empty(s) || 
    		// 		has_higher_precedence((char) stack_peek(s), *input)) ||
    		// 		has_equal_precedence((char) stack_peek(s), *input) &&
    		// 		no_left_bracket(stack_peek(s))) {
    		// 	putchar(stack_peek(s));
    		// 	stack_pop(s);
    		// }
			stack_push(s, *input);
    	}
    	if (!no_left_bracket(*input)) {
    		stack_push(s, *input);
    	}
    	input++;
	}
	stack_cleanup(s);
	return 0;
}

// while there are tokens to be read:
//     read a token.
//     if the token is a number, then:
//         push it to the output queue.
//     if the token is a function then:
//         push it onto the operator stack 
//     if the token is an operator, then:
//         while ((there is a function at the top of the operator stack)
//                or (there is an operator at the top of the operator stack with greater precedence)
//                or (the operator at the top of the operator stack has equal precedence and is left associative))
//               and (the operator at the top of the operator stack is not a left bracket):
//             pop operators from the operator stack onto the output queue.
//         push it onto the operator stack.
//     if the token is a left bracket (i.e. "("), then:
//         push it onto the operator stack.
//     if the token is a right bracket (i.e. ")"), then:
//         while the operator at the top of the operator stack is not a left bracket:
//             pop the operator from the operator stack onto the output queue.
//         pop the left bracket from the stack.
//         /* if the stack runs out without finding a left bracket, then there are mismatched parentheses. */
// if there are no more tokens to read:
//     while there are still operator tokens on the stack:
//         /* if the operator token on the top of the stack is a bracket, then there are mismatched parentheses. */
//         pop the operator from the operator stack onto the output queue.
// exit.

//     for (i=0; i<len; i++) {
//     	if (isdigit(input[i])) {
//     		stack_push(s, input[i]);
//     	}
//     	else {
//     		if (stack_empty(o)) {
//     			stack_push(o, input[i]);
//     		}
//     		else {
//     			if (has_higher_precedence( (char) stack_peek(o), input[i])) {
//     				stack_push(s, (char) stack_peek(o));
//     				stack_pop(o);
//     				stack_push(o, input[i]);
//     			}
//     			else {
//     				stack_push(o, input[i]);
//     			}
//     		}
//     	}
//     }

//     for (i = size_stack(o); i >= 0; i--) {
//     	printf("%d ", (char))
//     	stack_pop(o);
//     }

//  //    for (i = size_stack(s); i >= 0; i--) {
//  //    	printf("%c ", stack_peek(s)); 
//  //    	stack_pop(s);	
// 	// }

// 	stack_cleanup(s);
//     return 0;
// }

