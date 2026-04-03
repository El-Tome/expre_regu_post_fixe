#include "main.h"

#include <stdio.h>
#include <string.h>

#include "stack.h"

int priorite(char c) {
    switch (c) {
        case '\\':
            return 0;
        case '|':
            return 1;
        case '.':
            return 2;
        case '?':
            return 3;
        case '+':
            return 4;
        case '*':
            return 5;
        default:
            return -1;
    }
}

char * shunting_yard_explicite(char * e) {
    char tmp[1000];
    int i = 0;
    Stack p = s_create_empty_stack_char();
    if (p == NULL) {
        return NULL;
    }

    while (*e != '\0') {
        switch (*e) {
            case '(': {
                s_push_char(p, *e);
                break;
            }
            case ')': {
                while (s_read_char(p) != '(') {
                    tmp[i++] = s_pop_char(p);
                }
                s_pop_char(p);
                break;
            }
            case '.':
            case '|':
            case '*': {
                while (!s_is_empty(p) && priorite(s_read_char(p)) >= priorite(*e)) {
                    tmp[i++] = s_pop_char(p);
                }
                s_push_char(p, *e);
                break;
            }


            default: {
                tmp[i++] = *e;
            }
        }
        e++;
    }
    while (!s_is_empty(p)) {
        tmp[i++] = s_pop_char(p);
    }
    tmp[i] = '\0';

    return strdup(tmp);
}

char * shuting_yard(char * e) {
    char tmp[1000], prev = '\0';
    int i = 0;

    while (*e != '\0') {
        if (
            prev != '\0' &&
            (
                (priorite(prev) == -1 && prev != '(') ||
                prev == ')'                           ||
                priorite(prev) >= priorite('?')
            ) && (
                priorite(*e) == -1 ||
                *e == '('
            )
        ) {
            tmp[i++] = '.';
        }
        tmp[i++] = *e;
        prev = *e;
        e++;
    }
    tmp[i] = '\0';

    return shunting_yard_explicite(tmp);
}

int main() {
    printf("Entrer une expression\n");
    char express[1000], * post_fixe, *implicite;
    scanf("%s", express);

    post_fixe = shunting_yard_explicite(express);
    implicite = shuting_yard(express);

    printf("%s\n %s\n", post_fixe, implicite);


    return 0;
}