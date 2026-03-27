#include "list.h"

#include <stdio.h>
#include <stdlib.h>


struct simple_int_node_t {
    int val;
    struct simple_int_node_t *next;
};


typedef enum {
    LIST_INT = 0
} type_list;

typedef union {
    struct simple_int_node_t * simple_int_node;
} node_list;

typedef struct simple_list {
    type_list type;
    node_list head;
    node_list tail;
    int size;
} simple_list;

int is_empty(Simple_list l) {
    return l->size == 0;
}

void clear_list(Simple_list l) {}
void destroy_list(Simple_list l) {}
void show_list(Simple_list l) {}

Simple_list create_empty_stack_int() {
    Simple_list l;
    l = (Simple_list) malloc(sizeof(Simple_list));
    if (l == NULL) {
        fprintf(stderr, "Problème de mémoire\n");
        return NULL;
    }
    l->type = LIST_INT;
    l->head.simple_int_node = NULL;
    l->size = 0;

    return l;
}

void push_int(Simple_list l, int val) {
    if (l->type == LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }

    struct simple_int_node_t * new_node;
    new_node = (struct simple_int_node_t *) malloc(sizeof(struct simple_int_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }

    new_node->val = val;
    new_node->next = NULL;
    if (l->size == 0) {
        l->head.simple_int_node = new_node;
        l->tail = l->head;
    } else {
        l->tail.simple_int_node->next = new_node;
        l->tail.simple_int_node = new_node;
    }
    l->size++;
}

int pop_int(Simple_list l) {
    if (l->type != LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l->size == 0) {
        fprintf(stderr, "List vide\n");
        return 0;
    }
    struct simple_int_node_t* current = l->head.simple_int_node;
    while (current->next != l->tail.simple_int_node) {
        current = current->next;
    }

    int val = current->next->val;
    free(current->next);
    current->next = NULL;
    l->tail.simple_int_node = current;
    l->size--;

    return val;
}

int get_element(Simple_list l, int index) {
    if (l->type == LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l->size < index || index < 0) {
        fprintf(stderr, "Index incorrect\n");
    }

    struct simple_int_node_t* current = l->head.simple_int_node;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->val;
}

void remove_element(Simple_list l, int index) {
    if (l->type == LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    if (l->size < index || index < 0) {
        fprintf(stderr, "Index incorrect\n");
    }

    if (index == l->size - 1) {
        pop_int(l);
        return;
    }
    if (index == 0) {
        shift(l);
        return;
    }

    struct simple_int_node_t* current = l->head.simple_int_node;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    struct simple_int_node_t* to_free = current->next;
    current->next = current->next->next;
    free(to_free);
    l->size--;
}
int shift(Simple_list l) {
    if (l->type != LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l->size == 0) {
        fprintf(stderr, "List vide\n");
        return 0;
    }
    struct simple_int_node_t* current = l->head.simple_int_node;

    int val = current->val;
    l->head.simple_int_node = current->next;
    free(current);
    l->size--;

    return val;
}
void unshift(Simple_list l, int val) {
    if (l->type == LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }

    struct simple_int_node_t * new_node;
    new_node = (struct simple_int_node_t *) malloc(sizeof(struct simple_int_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }

    new_node->val = val;
    new_node->next = l->head.simple_int_node;
    if (l->size == 0) {
        l->head.simple_int_node = new_node;
        l->tail = l->head;
    } else {
        l->head.simple_int_node = new_node;
    }
    l->size++;
}

