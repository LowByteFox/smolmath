#include "env.h"
#include "array_kv.h"
#include <stdint.h>
#include "parser.h"

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void env_new(struct env *env)
{
    (void) env;
}

void env_free(struct env *env)
{
    kv_free(&env->vars);
    kv_free(&env->fns);
}

struct ast *env_get_var(struct env *env, const char *name)
{
    return kv_get(&env->vars, name);
}

struct ast *eval(struct env *env, struct ast *node)
{
    switch (node->type) {
    case NUMBER:
        return node;
    case BRACKETS:
        return eval(env, node->bracket);
    case ADD:
    {
        struct ast *left = eval(env, node->operation.left);
        struct ast *right = eval(env, node->operation.right);
        return number_node(left->value + right->value);
    }
    case SUB:
    {
        struct ast *left = eval(env, node->operation.left);
        struct ast *right = eval(env, node->operation.right);
        return number_node(left->value - right->value);
    }
    case MUL:
    {
        struct ast *left = eval(env, node->operation.left);
        struct ast *right = eval(env, node->operation.right);
        return number_node(left->value * right->value);
    }
    case DIV:
    {
        struct ast *left = eval(env, node->operation.left);
        struct ast *right = eval(env, node->operation.right);
        return number_node(left->value / right->value);
    }
    case EXP:
    {
        struct ast *left = eval(env, node->operation.left);
        struct ast *right = eval(env, node->operation.right);

#if BACKEND_FLOAT32
        return number_node(powf(left->value, right->value));
#elif BACKEND_FLOAT64
        return number_node(pow(left->value, right->value));
#elif BACKEND_FLOAT128
        return number_node(powl(left->value, right->value));
#endif
    }
    case VARIABLE:
        return kv_get(&env->vars, node->name);
    case ASSIGN:
    {
        struct ast *val = eval(env, node->assign.value);
        kv_add(&env->vars, node->assign.name, val);
        return val;
    }
    default:
        return NULL;
    }
}

struct ast *env_eval(struct env *env, const char *text)
{
    struct ast *parsed = parse(text);

    return eval(env, parsed);
}
