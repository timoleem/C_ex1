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

    char *input = argv[1];

    struct stack *s = stack_init();

    printf("%d", stack_pop(s));

    // int h = stack_push(s, 3);
    // printf("%d", h);
    // int top = stack_peek(s);
    // printf("%d", top);

    // int len = strlen(input);
    // int i = 0;
    // char stack[len];

    // for(i=0;i<len;i++) {
    // 	if (isdigit(input[i])) {
    // 		printf("%c",input[i]);
    // 	} 
    // }


    

    // ... SOME CODE MISSING HERE ...

    // stack_cleanup(s);

    return 0;
}
