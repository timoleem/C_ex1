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

    int len = strlen(input);
    int i = 0;

    for (i=0; i<len; i++) {
    	if (isdigit(input[i])) {
    		stack_push(s, input[i]);
    		printf("%c \n",input[i]);
    	} 
    }

    printf("stats \n");

    return 0;
}

// $ gcc -o testncurses.o -lncurses testncurses.c
