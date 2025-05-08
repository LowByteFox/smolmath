#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "parser.h"

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

int main() {
    char *str;
    do {
        printf("> ");
        fflush(stdout);
        str = readline();

        describe_node(parse(str));

        free(str);
    } while (str != NULL);
    return 0;
}
