#ifndef TP1_LIST_H
#define TP1_LIST_H

typedef struct simple_list *Simple_list;

/* Fonctions globales */
int is_empty_list(Simple_list l);
void clear_list(Simple_list l);
void destroy_list(Simple_list l);
void show_list(Simple_list l);
int is_circular(Simple_list l);

/* Fonctions pour les listes de INT */
Simple_list create_empty_list_int();
void push_int(Simple_list l, int val);
int pop_int(Simple_list l);
int get_element_int(Simple_list l, int index);
void remove_element_int(Simple_list l, int index);
int shift_int(Simple_list l);
void unshift_int(Simple_list l, int val);

/* Fonctions pour les listes de CHAR */
Simple_list create_empty_list_char();
void push_char(Simple_list l, char val);
char pop_char(Simple_list l);
char get_element_char(Simple_list l, int index);
void remove_element_char(Simple_list l, int index);
char shift_char(Simple_list l);
void unshift_char(Simple_list l, char val);

/* Fonctions pour les listes de FLOAT */
Simple_list create_empty_list_float();
void push_float(Simple_list l, float val);
float pop_float(Simple_list l);
float get_element_float(Simple_list l, int index);
void remove_element_float(Simple_list l, int index);
float shift_float(Simple_list l);
void unshift_float(Simple_list l, float val);

/* Fonctions pour les listes génériques */
Simple_list create_empty_list_generic(void (*free_func)(void *));
void push_generic(Simple_list l, void *val);
void *pop_generic(Simple_list l);
void *get_element_generic(Simple_list l, int index);
void remove_element_generic(Simple_list l, int index);
void *shift_generic(Simple_list l);
void unshift_generic(Simple_list l, void *val);

#endif //TP1_LIST_H
