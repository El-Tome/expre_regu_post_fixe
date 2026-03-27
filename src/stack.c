#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

/* Définitions internes */
struct node_int_stack {
    int val;
    struct node_int_stack* prev;
};

struct node_char_stack {
    char val;
    struct node_char_stack* prev;
};

struct node_float_stack {
    float val;
    struct node_float_stack* prev;
};

struct node_generic_stack {
    void * val;
    struct node_generic_stack* prev;
};


typedef enum {
    STACK_INT = 0,
    STACK_CHAR = 1,
    STACK_FLOAT = 2,
    STACK_GENERIC_STRUCT = 3
} type_stack;

typedef union {
    struct node_int_stack* node_int_stack;
    struct node_char_stack* node_char_stack;
    struct node_float_stack* node_float_stack;
    struct node_generic_stack* node_generic_stack;
} node_stack;

struct stack {
    type_stack type;
    node_stack node_stack;
    int size;
    void (*free_func)(void *);
};


/* Fonctions globales */
int is_empty(Stack s) {
    return s->size == 0;
}

static void clear_stack_int(Stack s) {
    while (!is_empty(s)) {
        pop_int(s);
    }
}

static void clear_stack_char(Stack s) {
    while (!is_empty(s)) {
        pop_char(s);
    }
}

static void clear_stack_float(Stack s) {
    while (!is_empty(s)) {
        pop_float(s);
    }
}

static void clear_stack_generic(Stack s) {
    void * elem;
    while (!is_empty(s)) {
        elem = pop_generic(s);
        s->free_func(elem);
    }
}


void clear_stack(Stack s) {
    switch (s->type) {
    case STACK_INT:
        clear_stack_int(s);
        break;
    case STACK_CHAR:
        clear_stack_char(s);
        break;
    case STACK_FLOAT:
        clear_stack_float(s);
        break;
    case STACK_GENERIC_STRUCT:
        clear_stack_generic(s);
        break;
    default:
        fprintf(stderr, "Erreur type invalide\n");
        break;
    }
}

void destroy_stack(Stack s) {
    clear_stack(s);
    free(s);
    s = NULL;
}


void show_stack(Stack s) {
    node_stack node;
    switch (s->type) {
    case STACK_INT: {
        node.node_int_stack = s->node_stack.node_int_stack;
        while (node.node_int_stack) {
            printf("%d\n", node.node_int_stack->val);
            node.node_int_stack = node.node_int_stack->prev;
        }
        break;
    }
    case STACK_CHAR: {
        node.node_char_stack = s->node_stack.node_char_stack;
        while (node.node_char_stack) {
            printf("%c\n", node.node_char_stack->val);
            node.node_char_stack = node.node_char_stack->prev;
        }
        break;
    }
    case STACK_FLOAT: {
        node.node_float_stack = s->node_stack.node_float_stack;
        while (node.node_float_stack) {
            printf("%f\n", node.node_float_stack->val);
            node.node_float_stack = node.node_float_stack->prev;
        }
        break;
    }
    case STACK_GENERIC_STRUCT: {
        printf("Impossible d'afficher la structure de donnée\n");
        break;
    }
    }
}


/* Partie INT */
Stack create_empty_stack_int() {
    Stack s = malloc(sizeof(struct stack));
    if (s == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return NULL;
    }

    s->type = STACK_INT;
    s->node_stack.node_int_stack = NULL;
    s->size = 0;

    return s;
}

void push_int(Stack s, int val) {
    if (s->type != STACK_INT) {
        fprintf(stderr, "Type de stack invalide\n");
        return;
    }

    struct node_int_stack* new_node = malloc(sizeof(struct node_int_stack));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }

    new_node->val = val;
    new_node->prev = s->node_stack.node_int_stack;
    s->node_stack.node_int_stack = new_node;
    s->size++;
}

int pop_int(Stack s) {
    if (s->type != STACK_INT) {
        fprintf(stderr, "Type de stack invalide\n");
        return 0;
    }
    if (is_empty(s)) {
        fprintf(stderr, "Erreur la stack est vide\n");
        return 0;
    }

    struct node_int_stack* node = s->node_stack.node_int_stack;
    int val = node->val;

    s->node_stack.node_int_stack = node->prev;
    free(node);
    s->size--;

    return val;
}


/* Fonctions pour les stacks de CHAR */
Stack create_empty_stack_char() {
    Stack s = malloc(sizeof(struct stack));
    if (s == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return NULL;
    }

    s->type = STACK_CHAR;
    s->node_stack.node_char_stack = NULL;
    s->size = 0;

    return s;
}

void push_char(Stack s, char val) {
    if (s->type != STACK_CHAR) {
        fprintf(stderr, "Type de stack invalide\n");
        return;
    }

    struct node_char_stack* new_node = malloc(sizeof(struct node_char_stack));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }

    new_node->val = val;
    new_node->prev = s->node_stack.node_char_stack;
    s->node_stack.node_char_stack = new_node;
    s->size++;
}

char pop_char(Stack s) {
    if (s->type != STACK_CHAR) {
        fprintf(stderr, "Type de stack invalide\n");
        return 0;
    }
    if (is_empty(s)) {
        fprintf(stderr, "Erreur la stack est vide\n");
        return 0;
    }

    struct node_char_stack* node = s->node_stack.node_char_stack;
    char val = node->val;

    s->node_stack.node_char_stack = node->prev;
    free(node);
    s->size--;

    return val;
}

Stack create_empty_stack_float() {
    Stack s = malloc(sizeof(struct stack));
    if (s == NULL) {
        fprintf(stderr, "Erreur de mémoire");
        return NULL;
    }
    s->type = STACK_FLOAT;
    s->node_stack.node_float_stack = NULL;
    s->size = 0;
    return s;
}

void push_float(Stack s, float val) {
    if (s->type != STACK_FLOAT) {
        fprintf(stderr, "Type de stack invalide\n");
        return;
    }
    struct node_float_stack* new_node = malloc(sizeof(struct node_float_stack));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire");
        return;
    }
    new_node->val = val;
    new_node->prev = s->node_stack.node_float_stack;
    s->node_stack.node_float_stack = new_node;
    s->size++;
}

float pop_float(Stack s) {
    if (s->type != STACK_FLOAT) {
        fprintf(stderr, "Type de stack invalide\n");
        return 0;
    }
    if (is_empty(s)) {
        fprintf(stderr, "Erreur la stack est vide\n");
        return 0;
    }
    struct node_float_stack* node = s->node_stack.node_float_stack;
    float val = node->val;

    s->node_stack.node_float_stack = node->prev;
    free(node);
    s->size--;

    return val;
}


/* Stack sur des structures de donnée */
Stack create_empty_stack_generic(void (*free_func)(void *)) {
    if (free_func == NULL) {
        fprintf(stderr, "Erreur aucune fonction de free pour le pointeur");
        return NULL;
    }

    Stack s = malloc(sizeof(struct stack));
    if (s == NULL) {
        fprintf(stderr, "Erreur de mémoire");
        return NULL;
    }

    s->type = STACK_GENERIC_STRUCT;
    s->node_stack.node_generic_stack = NULL;
    s->size = 0;
    s->free_func = free_func;
    return s;
}

void push_generic(Stack s, void* val) {
    if (s->type != STACK_GENERIC_STRUCT) {
        fprintf(stderr, "Type de stack invalide\n");
        return;
    }
    struct node_generic_stack* new_node = malloc(sizeof(struct node_generic_stack));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire");
        return;
    }
    new_node->val = val;
    new_node->prev = s->node_stack.node_generic_stack;
    s->node_stack.node_generic_stack = new_node;
    s->size++;
}

void* pop_generic(Stack s) {
    if (s->type != STACK_GENERIC_STRUCT) {
        fprintf(stderr, "Type de stack invalide\n");
        return NULL;
    }
    if (is_empty(s)) {
        fprintf(stderr, "Erreur la stack est vide\n");
        return NULL;
    }
    struct node_generic_stack* node = s->node_stack.node_generic_stack;
    void* val = node->val;

    s->node_stack.node_generic_stack = node->prev;
    free(node);
    s->size--;

    return val;
}

