#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <config.h>
#include <string.h>

#include "ast.h"
#include "env.h"

char* readline(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);

    if (read == -1) {
        free(line);
        return NULL;
    }

    return line;
}

void print_node(struct env *env, struct ast *node)
{
    if (node == NULL) {
        printf("nil");
        return;
    }

    switch (node->type){
    case NUMBER:
#if BACKEND_FLOAT32
        if (node->value == floorf(node->value))
            printf("%.0f", node->value);
        else
            printf("%f", node->value);
#elif BACKEND_FLOAT64
        if (node->value == floor(node->value))
            printf("%.0f", node->value);
        else
            printf("%f", node->value);
#elif BACKEND_FLOAT128
        if (node->value == floorl(node->value))
            printf("%.0Lf", node->value);
        else
            printf("%Lf", node->value);
#endif
        break;
    case VARIABLE:
        struct ast *res = env_get_var(env, node->name);
        print_node(env, res);
        break;
    default:
        printf("???");
    }
}

int main() {
    struct env env = {0};
    env_new(&env);

    char *str;
    do {
        printf("> ");
        fflush(stdout);
        str = readline();

        if (strcmp(str, ".exit\n") == 0)
            return 0;

        print_node(&env, env_eval(&env, str));
        putchar('\n');

        free(str);
    } while (str != NULL);
    return 0;
}
