#ifndef TP1_LIST_H
#define TP1_LIST_H

typedef struct simple_list *Simple_list;

/* Fonctions globales */
int l_is_empty_list(Simple_list l);
void l_clear_list(Simple_list l);
void l_destroy_list(Simple_list l);
void l_show_list(Simple_list l);
int l_is_circular(Simple_list l);

/* Fonctions pour les listes de INT */
Simple_list l_create_empty_list_int();
void l_push_int(Simple_list l, int val);
int l_pop_int(Simple_list l);
int l_get_element_int(Simple_list l, int index);
void l_remove_element_int(Simple_list l, int index);
int l_shift_int(Simple_list l);
void l_unshift_int(Simple_list l, int val);

/* Fonctions pour les listes de CHAR */
Simple_list l_create_empty_list_char();
void l_push_char(Simple_list l, char val);
char l_pop_char(Simple_list l);
char l_get_element_char(Simple_list l, int index);
void l_remove_element_char(Simple_list l, int index);
char l_shift_char(Simple_list l);
void l_unshift_char(Simple_list l, char val);

/* Fonctions pour les listes de FLOAT */
Simple_list l_create_empty_list_float();
void l_push_float(Simple_list l, float val);
float l_pop_float(Simple_list l);
float l_get_element_float(Simple_list l, int index);
void l_remove_element_float(Simple_list l, int index);
float l_shift_float(Simple_list l);
void l_unshift_float(Simple_list l, float val);

/* Fonctions pour les listes génériques */
Simple_list l_create_empty_list_generic(void (*free_func)(void *));
void l_push_generic(Simple_list l, void *val);
void *l_pop_generic(Simple_list l);
void *l_get_element_generic(Simple_list l, int index);
void l_remove_element_generic(Simple_list l, int index);
void *l_shift_generic(Simple_list l);
void l_unshift_generic(Simple_list l, void *val);

#endif //TP1_LIST_H
