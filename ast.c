#include "ast.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct ast *number_node(uint64_t value)
{
    struct ast *n = calloc(1, sizeof(*n));
    n->type = NUMBER;
    n->value = value;
    
    return n;
}

struct ast *variable_node(struct str str)
{
    struct ast *n = calloc(1, sizeof(*n));
    n->type = VARIABLE;
    n->name = strndup(str.str, str.len);

    return n;
}

struct ast *bracket_node(struct ast *expr)
{
    struct ast *n = calloc(1, sizeof(*n));
    n->type = BRACKETS;
    n->bracket = expr;

    return n;
}

struct ast *operation_node(enum node_type type, struct ast *left, struct ast *right)
{
    struct ast *n = calloc(1, sizeof(*n));
    n->type = type;
    n->operation.left = left;
    n->operation.right = right;

    return n;
}

struct ast *fn_def_node(struct str str, struct ast *expr)
{
    struct ast *n = calloc(1, sizeof(*n));
    n->type = FUNCTION_DEF;
    n->fn_def.name = strndup(str.str, str.len);
    n->fn_def.expr = expr;

    return n;
}

struct ast *fn_call_node(struct str str, struct ast *arg)
{
    struct ast *n = calloc(1, sizeof(*n));
    n->type = FUNCTION_CALL;
    n->fn_call.name = strndup(str.str, str.len);
    n->fn_call.first_arg = arg;

    return n;
}

struct ast *fn_arg_node(struct ast *list, struct ast *expr)
{
    struct ast *n = calloc(1, sizeof(*n));
    n->type = FUNCTION_ARG;
    n->fn_arg.expr = expr;
    n->fn_arg.next_arg = list;

    return n;
}

static void _describe(struct ast *ast, int span)
{
    int move = span;
    for (;move;move--)
        putchar('\t');

    switch (ast->type) {
    case NUMBER:
        printf("Number => %ld\n", ast->value);
        break;
    case VARIABLE:
        printf("Variable => %s\n", ast->name);
        break;
    case BRACKETS:
        printf("Brackets => (\n");
        _describe(ast->bracket, span + 1);
        int move = span;
        for (;move;move--)
            putchar('\t');
        printf(")\n");
        break;
    case ADD:
        printf("+ =>\n");
        _describe(ast->operation.left, span + 1);
        _describe(ast->operation.right, span + 1);
        break;
    case SUB:
        printf("- =>\n");
        _describe(ast->operation.left, span + 1);
        _describe(ast->operation.right, span + 1);
        break;
    case MUL:
        printf("* =>\n");
        _describe(ast->operation.left, span + 1);
        _describe(ast->operation.right, span + 1);
        break;
    case DIV:
        printf("/ =>\n");
        _describe(ast->operation.left, span + 1);
        _describe(ast->operation.right, span + 1);
        break;
    case FUNCTION_DEF:
        printf("def %s() =>\n", ast->fn_def.name);
        _describe(ast->fn_def.expr, span + 1);
        break;
    case FUNCTION_CALL:
        printf("call %s() =>\n", ast->fn_call.name);
        if (ast->fn_call.first_arg != NULL)
            _describe(ast->fn_call.first_arg, span + 1);
        break;
    case FUNCTION_ARG:
        printf("fn arg =>\n");
        _describe(ast->fn_arg.expr, span + 1);
        if (ast->fn_arg.next_arg != NULL)
            _describe(ast->fn_arg.next_arg, span);
        break;
    }
}

void describe_node(struct ast *ast)
{
    _describe(ast, 0);
}

void free_node(struct ast *ast)
{

}
