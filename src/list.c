#include "list.h"

#include <stdio.h>
#include <stdlib.h>

/* Définitions internes */
struct simple_int_node_t {
    int val;
    struct simple_int_node_t *next;
};

struct simple_char_node_t {
    char val;
    struct simple_char_node_t *next;
};

struct simple_float_node_t {
    float val;
    struct simple_float_node_t *next;
};

struct simple_generic_node_t {
    void *val;
    struct simple_generic_node_t *next;
};


typedef enum {
    LIST_INT = 0,
    LIST_CHAR = 1,
    LIST_FLOAT = 2,
    LIST_GENERIC = 3
} type_list;

typedef union {
    struct simple_int_node_t     *simple_int_node;
    struct simple_char_node_t    *simple_char_node;
    struct simple_float_node_t   *simple_float_node;
    struct simple_generic_node_t *simple_generic_node;
} node_list;

typedef struct simple_list {
    type_list type;
    node_list head;
    node_list tail;
    int size;
    void (*free_func)(void *);
    int l_is_circular;
} simple_list;


/* Fonctions globales */
int l_is_empty_list(Simple_list l) {
    return l->size == 0;
}

static void clear_list_int(Simple_list l) {
    while (!l_is_empty_list(l)) {
        l_pop_int(l);
    }
}

static void clear_list_char(Simple_list l) {
    while (!l_is_empty_list(l)) {
        l_pop_char(l);
    }
}

static void clear_list_float(Simple_list l) {
    while (!l_is_empty_list(l)) {
        l_pop_float(l);
    }
}

static void clear_list_generic(Simple_list l) {
    while (!l_is_empty_list(l)) {
        void *elem = l_pop_generic(l);
        l->free_func(elem);
    }
}

void l_clear_list(Simple_list l) {
    switch (l->type) {
    case LIST_INT:
        clear_list_int(l);
        break;
    case LIST_CHAR:
        clear_list_char(l);
        break;
    case LIST_FLOAT:
        clear_list_float(l);
        break;
    case LIST_GENERIC:
        clear_list_generic(l);
        break;
    default:
        fprintf(stderr, "Erreur type invalide\n");
        break;
    }
}

void l_destroy_list(Simple_list l) {
    l_clear_list(l);
    free(l);
}

void l_set_circular(Simple_list l, int circular) {
    if (l == NULL) {
        fprintf(stderr, "Liste invalide\n");
        return;
    }
    l->l_is_circular = circular;
    if (circular && l->size > 0) {
        switch (l->type) {
        case LIST_INT:
            l->tail.simple_int_node->next = l->head.simple_int_node;
            break;
        case LIST_CHAR:
            l->tail.simple_char_node->next = l->head.simple_char_node;
            break;
        case LIST_FLOAT:
            l->tail.simple_float_node->next = l->head.simple_float_node;
            break;
        case LIST_GENERIC:
            l->tail.simple_generic_node->next = l->head.simple_generic_node;
            break;
        }
    } else if (!circular && l->size > 0) {
        switch (l->type) {
        case LIST_INT:
            l->tail.simple_int_node->next = NULL;
            break;
        case LIST_CHAR:
            l->tail.simple_char_node->next = NULL;
            break;
        case LIST_FLOAT:
            l->tail.simple_float_node->next = NULL;
            break;
        case LIST_GENERIC:
            l->tail.simple_generic_node->next = NULL;
            break;
        }
    }
}

int l_is_circular(Simple_list l) {
    if (l == NULL) {
        return 0;
    }
    return l->l_is_circular;
}

void l_show_list(Simple_list l) {
    switch (l->type) {
    case LIST_INT: {
        struct simple_int_node_t *current = l->head.simple_int_node;
        for (int i = 0; i < l->size; ++i) {
            printf("%d\n", current->val);
            current = current->next;
        }
        break;
    }
    case LIST_CHAR: {
        struct simple_char_node_t *current = l->head.simple_char_node;
        for (int i = 0; i < l->size; ++i) {
            printf("%c\n", current->val);
            current = current->next;
        }
        break;
    }
    case LIST_FLOAT: {
        struct simple_float_node_t *current = l->head.simple_float_node;
        for (int i = 0; i < l->size; ++i) {
            printf("%f\n", current->val);
            current = current->next;
        }
        break;
    }
    case LIST_GENERIC:
        printf("Impossible d'afficher la structure de donnée\n");
        break;
    default:
        fprintf(stderr, "Erreur type invalide\n");
        break;
    }
}


/* Fonctions pour les listes de INT */
Simple_list l_create_empty_list_int() {
    Simple_list l = malloc(sizeof(simple_list));
    if (l == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return NULL;
    }
    l->type = LIST_INT;
    l->head.simple_int_node = NULL;
    l->tail.simple_int_node = NULL;
    l->size = 0;
    l->l_is_circular = 0;
    return l;
}

void l_push_int(Simple_list l, int val) {
    if (l->type != LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    struct simple_int_node_t *new_node = malloc(sizeof(struct simple_int_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }
    new_node->val = val;
    new_node->next = NULL;
    if (l->size == 0) {
        l->head.simple_int_node = new_node;
        l->tail.simple_int_node = new_node;
    } else {
        l->tail.simple_int_node->next = new_node;
        l->tail.simple_int_node = new_node;
    }
    if (l->l_is_circular) {
        l->tail.simple_int_node->next = l->head.simple_int_node;
    }
    l->size++;
}

int l_pop_int(Simple_list l) {
    if (l->type != LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l_is_empty_list(l)) {
        fprintf(stderr, "List vide\n");
        return 0;
    }
    int val;
    if (l->size == 1) {
        val = l->head.simple_int_node->val;
        free(l->head.simple_int_node);
        l->head.simple_int_node = NULL;
        l->tail.simple_int_node = NULL;
        l->size--;
        return val;
    }

    struct simple_int_node_t *current = l->head.simple_int_node;
    while (current->next != l->tail.simple_int_node) {
        current = current->next;
    }
    val = l->tail.simple_int_node->val;
    free(l->tail.simple_int_node);
    if (l->l_is_circular) {
        current->next = l->head.simple_int_node;
    } else {
        current->next = NULL;
    }

    l->tail.simple_int_node = current;
    l->size--;
    return val;
}

int l_get_element_int(Simple_list l, int index) {
    if (l->type != LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Index incorrect\n");
        return 0;
    }
    struct simple_int_node_t *current = l->head.simple_int_node;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->val;
}

void l_remove_element_int(Simple_list l, int index) {
    if (l->type != LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Index incorrect\n");
        return;
    }
    if (index == l->size - 1) {
        l_pop_int(l);
        return;
    }
    if (index == 0) {
        l_shift_int(l);
        return;
    }
    struct simple_int_node_t *current = l->head.simple_int_node;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    struct simple_int_node_t *to_free = current->next;
    current->next = to_free->next;
    free(to_free);
    l->size--;
}

int l_shift_int(Simple_list l) {
    if (l->type != LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l_is_empty_list(l)) {
        fprintf(stderr, "List vide\n");
        return 0;
    }
    struct simple_int_node_t *current = l->head.simple_int_node;
    int val = current->val;
    l->head.simple_int_node = current->next;
    if (l->l_is_circular) {
        l->tail.simple_int_node->next = l->head.simple_int_node;
    } else {
        l->tail.simple_int_node->next = NULL;
    }
    free(current);
    l->size--;
    return val;
}

void l_unshift_int(Simple_list l, int val) {
    if (l->type != LIST_INT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    struct simple_int_node_t *new_node = malloc(sizeof(struct simple_int_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }
    new_node->val = val;
    new_node->next = l->head.simple_int_node;
    l->head.simple_int_node = new_node;
    if (l->size == 0) {
        l->tail.simple_int_node = new_node;
    }
    if (l->l_is_circular) {
        l->tail.simple_int_node->next = new_node;
    }
    l->size++;
}


/* Fonctions pour les listes de CHAR */
Simple_list l_create_empty_list_char() {
    Simple_list l = malloc(sizeof(simple_list));
    if (l == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return NULL;
    }
    l->type = LIST_CHAR;
    l->head.simple_char_node = NULL;
    l->tail.simple_char_node = NULL;
    l->size = 0;
    l->l_is_circular = 0;
    return l;
}

void l_push_char(Simple_list l, char val) {
    if (l->type != LIST_CHAR) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    struct simple_char_node_t *new_node = malloc(sizeof(struct simple_char_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }
    new_node->val = val;
    new_node->next = NULL;
    if (l->size == 0) {
        l->head.simple_char_node = new_node;
        l->tail.simple_char_node = new_node;
    } else {
        l->tail.simple_char_node->next = new_node;
        l->tail.simple_char_node = new_node;
    }
    if (l->l_is_circular) {
        l->tail.simple_char_node->next = l->head.simple_char_node;
    }
    l->size++;
}

char l_pop_char(Simple_list l) {
    if (l->type != LIST_CHAR) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l_is_empty_list(l)) {
        fprintf(stderr, "List vide\n");
        return 0;
    }
    char val;
    if (l->size == 1) {
        val = l->head.simple_char_node->val;
        free(l->head.simple_char_node);
        l->head.simple_char_node = NULL;
        l->tail.simple_char_node = NULL;
        l->size--;
        return val;
    }

    struct simple_char_node_t *current = l->head.simple_char_node;
    while (current->next != l->tail.simple_char_node) {
        current = current->next;
    }

    val = l->tail.simple_char_node->val;
    free(l->tail.simple_char_node);
    if (l->l_is_circular) {
        current->next = l->head.simple_char_node;
    } else {
        current->next = NULL;
    }

    l->tail.simple_char_node = current;
    l->size--;
    return val;
}

char l_get_element_char(Simple_list l, int index) {
    if (l->type != LIST_CHAR) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Index incorrect\n");
        return 0;
    }
    struct simple_char_node_t *current = l->head.simple_char_node;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->val;
}

void l_remove_element_char(Simple_list l, int index) {
    if (l->type != LIST_CHAR) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Index incorrect\n");
        return;
    }
    if (index == l->size - 1) {
        l_pop_char(l);
        return;
    }
    if (index == 0) {
        l_shift_char(l);
        return;
    }
    struct simple_char_node_t *current = l->head.simple_char_node;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    struct simple_char_node_t *to_free = current->next;
    current->next = to_free->next;
    free(to_free);
    l->size--;
}

char l_shift_char(Simple_list l) {
    if (l->type != LIST_CHAR) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l_is_empty_list(l)) {
        fprintf(stderr, "List vide\n");
        return 0;
    }
    struct simple_char_node_t *current = l->head.simple_char_node;
    char val = current->val;
    l->head.simple_char_node = current->next;
    if (l->l_is_circular) {
        l->tail.simple_char_node->next = l->head.simple_char_node;
    } else {
        l->tail.simple_char_node->next = NULL;
    }
    free(current);
    l->size--;
    return val;
}

void l_unshift_char(Simple_list l, char val) {
    if (l->type != LIST_CHAR) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    struct simple_char_node_t *new_node = malloc(sizeof(struct simple_char_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }
    new_node->val = val;
    new_node->next = l->head.simple_char_node;
    l->head.simple_char_node = new_node;
    if (l->size == 0) {
        l->tail.simple_char_node = new_node;
    }
    if (l->l_is_circular) {
        l->tail.simple_char_node->next = new_node;
    }
    l->size++;
}


/* Fonctions pour les listes de FLOAT */
Simple_list l_create_empty_list_float() {
    Simple_list l = malloc(sizeof(simple_list));
    if (l == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return NULL;
    }
    l->type = LIST_FLOAT;
    l->head.simple_float_node = NULL;
    l->tail.simple_float_node = NULL;
    l->size = 0;
    l->l_is_circular = 0;
    return l;
}

void l_push_float(Simple_list l, float val) {
    if (l->type != LIST_FLOAT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    struct simple_float_node_t *new_node = malloc(sizeof(struct simple_float_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }
    new_node->val = val;
    new_node->next = NULL;
    if (l->size == 0) {
        l->head.simple_float_node = new_node;
        l->tail.simple_float_node = new_node;
    } else {
        l->tail.simple_float_node->next = new_node;
        l->tail.simple_float_node = new_node;
    }
    if (l->l_is_circular) {
        l->tail.simple_float_node->next = l->head.simple_float_node;
    }
    l->size++;
}

float l_pop_float(Simple_list l) {
    if (l->type != LIST_FLOAT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l_is_empty_list(l)) {
        fprintf(stderr, "List vide\n");
        return 0;
    }
    float val;
    if (l->size == 1) {
        val = l->head.simple_float_node->val;
        free(l->head.simple_float_node);
        l->head.simple_float_node = NULL;
        l->tail.simple_float_node = NULL;
        l->size--;
        return val;
    }
    struct simple_float_node_t *current = l->head.simple_float_node;
    while (current->next != l->tail.simple_float_node) {
        current = current->next;
    }
    val = l->tail.simple_float_node->val;
    free(l->tail.simple_float_node);
    if (l->l_is_circular) {
        current->next = l->head.simple_float_node;
    } else {
        current->next = NULL;
    }
    l->tail.simple_float_node = current;
    l->size--;
    return val;
}

float l_get_element_float(Simple_list l, int index) {
    if (l->type != LIST_FLOAT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Index incorrect\n");
        return 0;
    }
    struct simple_float_node_t *current = l->head.simple_float_node;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->val;
}

void l_remove_element_float(Simple_list l, int index) {
    if (l->type != LIST_FLOAT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Index incorrect\n");
        return;
    }
    if (index == l->size - 1) {
        l_pop_float(l);
        return;
    }
    if (index == 0) {
        l_shift_float(l);
        return;
    }
    struct simple_float_node_t *current = l->head.simple_float_node;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    struct simple_float_node_t *to_free = current->next;
    current->next = to_free->next;
    free(to_free);
    l->size--;
}

float l_shift_float(Simple_list l) {
    if (l->type != LIST_FLOAT) {
        fprintf(stderr, "Type de list invalide\n");
        return 0;
    }
    if (l_is_empty_list(l)) {
        fprintf(stderr, "List vide\n");
        return 0;
    }
    struct simple_float_node_t *current = l->head.simple_float_node;
    float val = current->val;
    l->head.simple_float_node = current->next;
    if (l->l_is_circular) {
        l->tail.simple_float_node->next = l->head.simple_float_node;
    } else {
        l->tail.simple_float_node = NULL;
    }
    free(current);
    l->size--;
    return val;
}

void l_unshift_float(Simple_list l, float val) {
    if (l->type != LIST_FLOAT) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    struct simple_float_node_t *new_node = malloc(sizeof(struct simple_float_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }
    new_node->val = val;
    new_node->next = l->head.simple_float_node;
    l->head.simple_float_node = new_node;
    if (l->size == 0) {
        l->tail.simple_float_node = new_node;
    }
    if (l->l_is_circular) {
        l->tail.simple_float_node->next = new_node;
    }
    l->size++;
}


/* Fonctions pour les listes génériques */
Simple_list l_create_empty_list_generic(void (*free_func)(void *)) {
    if (free_func == NULL) {
        fprintf(stderr, "Erreur aucune fonction de free pour le pointeur\n");
        return NULL;
    }
    Simple_list l = malloc(sizeof(simple_list));
    if (l == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return NULL;
    }
    l->type = LIST_GENERIC;
    l->head.simple_generic_node = NULL;
    l->tail.simple_generic_node = NULL;
    l->size = 0;
    l->free_func = free_func;
    l->l_is_circular = 0;
    return l;
}

void l_push_generic(Simple_list l, void *val) {
    if (l->type != LIST_GENERIC) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    struct simple_generic_node_t *new_node = malloc(sizeof(struct simple_generic_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }
    new_node->val = val;
    new_node->next = NULL;
    if (l->size == 0) {
        l->head.simple_generic_node = new_node;
        l->tail.simple_generic_node = new_node;
    } else {
        l->tail.simple_generic_node->next = new_node;
        l->tail.simple_generic_node = new_node;
    }
    if (l->l_is_circular) {
        l->tail.simple_generic_node->next = l->head.simple_generic_node;
    }
    l->size++;
}

void *l_pop_generic(Simple_list l) {
    if (l->type != LIST_GENERIC) {
        fprintf(stderr, "Type de list invalide\n");
        return NULL;
    }
    if (l_is_empty_list(l)) {
        fprintf(stderr, "List vide\n");
        return NULL;
    }
    void *val;
    if (l->size == 1) {
        val = l->head.simple_generic_node->val;
        free(l->head.simple_generic_node);
        l->head.simple_generic_node = NULL;
        l->tail.simple_generic_node = NULL;
        l->size--;
        return val;
    }
    struct simple_generic_node_t *current = l->head.simple_generic_node;
    while (current->next != l->tail.simple_generic_node) {
        current = current->next;
    }
    val = l->tail.simple_generic_node->val;
    free(l->tail.simple_generic_node);
    if (l->l_is_circular) {
        current->next = l->head.simple_generic_node;
    } else {
        current->next = NULL;
    }
    l->tail.simple_generic_node = current;
    l->size--;
    return val;
}

void *l_get_element_generic(Simple_list l, int index) {
    if (l->type != LIST_GENERIC) {
        fprintf(stderr, "Type de list invalide\n");
        return NULL;
    }
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Index incorrect\n");
        return NULL;
    }
    struct simple_generic_node_t *current = l->head.simple_generic_node;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->val;
}

void l_remove_element_generic(Simple_list l, int index) {
    if (l->type != LIST_GENERIC) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Index incorrect\n");
        return;
    }
    if (index == l->size - 1) {
        void *elem = l_pop_generic(l);
        l->free_func(elem);
        return;
    }
    if (index == 0) {
        void *elem = l_shift_generic(l);
        l->free_func(elem);
        return;
    }
    struct simple_generic_node_t *current = l->head.simple_generic_node;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    struct simple_generic_node_t *to_free = current->next;
    current->next = to_free->next;
    l->free_func(to_free->val);
    free(to_free);
    l->size--;
}

void *l_shift_generic(Simple_list l) {
    if (l->type != LIST_GENERIC) {
        fprintf(stderr, "Type de list invalide\n");
        return NULL;
    }
    if (l_is_empty_list(l)) {
        fprintf(stderr, "List vide\n");
        return NULL;
    }
    struct simple_generic_node_t *current = l->head.simple_generic_node;
    void *val = current->val;
    l->head.simple_generic_node = current->next;
    if (l->l_is_circular) {
        l->tail.simple_generic_node->next = l->head.simple_generic_node;
    } else {
        l->tail.simple_generic_node = NULL;
    }
    free(current);
    l->size--;
    return val;
}

void l_unshift_generic(Simple_list l, void *val) {
    if (l->type != LIST_GENERIC) {
        fprintf(stderr, "Type de list invalide\n");
        return;
    }
    struct simple_generic_node_t *new_node = malloc(sizeof(struct simple_generic_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur de mémoire\n");
        return;
    }
    new_node->val = val;
    new_node->next = l->head.simple_generic_node;
    l->head.simple_generic_node = new_node;
    if (l->size == 0) {
        l->tail.simple_generic_node = new_node;
    }
    if (l->l_is_circular) {
        l->tail.simple_generic_node->next = new_node;
    }
    l->size++;
}
