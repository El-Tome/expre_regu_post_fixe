#ifndef STACK_H
#define STACK_H

typedef struct stack *Stack;

/* Fonctions globales */
int s_is_empty(Stack s);
void s_clear_stack(Stack s);
void s_destroy_stack(Stack s);
void s_show_stack(Stack s);

/* Fonctions pour les stacks de INT */
Stack s_create_empty_stack_int();
void s_push_int(Stack s, int val);
int s_pop_int(Stack s);
int s_read_int(Stack s);

/* Fonctions pour les stacks de CHAR */
Stack s_create_empty_stack_char();
void s_push_char(Stack s, char val);
char s_pop_char(Stack s);
char s_read_char(Stack s);

/* Fonction sur les flotants */
Stack s_create_empty_stack_float();
void s_push_float(Stack s, float val);
float s_pop_float(Stack s);
float s_read_float(Stack s);

/* Fonction sur les pointeurs générique */
Stack s_create_empty_stack_generic(void (*free_func)(void*));
void s_push_generic(Stack s, void *val);
void *s_pop_generic(Stack s);
void *s_read_generic(Stack s);

#endif
