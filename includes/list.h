#ifndef TP1_LIST_H
#define TP1_LIST_H

typedef struct simple_list *Simple_list;


/* Fonctions globales */
int is_empty(Simple_list l);
void clear_list(Simple_list l);
void destroy_list(Simple_list l);
void show_list(Simple_list l);

/* Fonctions pour les listes simple de INT */
Simple_list create_empty_stack_int();
void push_int(Simple_list l, int val);
int pop_int(Simple_list l);
int get_element(Simple_list l, int index);
void remove_element(Simple_list l, int index);
int shift(Simple_list l);
void unshift(Simple_list l, int val);


#endif //TP1_LIST_H