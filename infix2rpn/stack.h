/* Handle to stack */
struct stack;

/* Expose stack size in header file for testing. */
#define STACK_SIZE 100


/* Return a pointer to a stack data structure if succesful, otherwise
 * return NULL.
 * Size of stack is fixed. */
struct stack *stack_init(void);

/* Cleanup stack.
 * Also prints the statistics. */
void stack_cleanup(struct stack *stack);

/* Push item onto the stack.
 * Return 0 if succesful, 1 otherwise. */
int stack_push(struct stack *stack, int e);

/* Pop item from stack and return it.
 * Return top item if succesful, -1 otherwise. */
int stack_pop(struct stack *stack);

/* Return top of item from stack. Leave stack unchanged.
 * Return top item if succesful, -1 otherwise. */
int stack_peek(struct stack *stack);

/* Return 1 if stack is empty, 0 if the stack contains any elements and
 * return -1 if the operation fails. */
int stack_empty(struct stack *stack);

/* Return the size of the stack as an integer */
int size_stack(struct stack *stack); 

/* Get the operator weight of one character */
int GetOperatorWeight(char op);

/* Check which operator has a higher precedence */
int has_higher_precedence(char op1, char op2);

/* Check if the token is a operator */
int isoperator(char token);

/* Check which operator has equal precedence */
int has_equal_precedence(char op1, char op2);

/* Check if token is not a left bracket */
int left_bracket (char token);

/* Check if token is not a right bracket */
int right_bracket (char token);

/* Check if token is valid */
int isinvalidtoken(char token);

/* Add push */
void add_push(struct stack *stack); 

/* Add pop */
void add_pop(struct stack *stack); 

/* Add max to dynamic int */
void add_max(struct stack *stack, int c);

/* Keep track of max stack length value */
void max(struct stack *stack);