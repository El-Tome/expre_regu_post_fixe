#ifndef STACK_H
#define STACK_H

typedef struct stack *Stack;

/* Fonctions globales */
int is_empty(Stack s);
void clear_stack(Stack s);
void destroy_stack(Stack s);
void show_stack(Stack s);

/* Fonctions pour les stacks de INT */
Stack create_empty_stack_int();
void push_int(Stack s, int val);
int pop_int(Stack s);

/* Fonctions pour les stacks de CHAR */
Stack create_empty_stack_char();
void push_char(Stack s, char val);
char pop_char(Stack s);

/* Fonction sur les flotants */
Stack create_empty_stack_float();
void push_float(Stack s, float val);
float pop_float(Stack s);

/* Fonction sur les pointeurs générique */
Stack create_empty_stack_generic(void (*free_func)(void*));
void push_generic(Stack s, void *val);
void *pop_generic(Stack s);

#endif
