#pragma once

#include "array_kv.h"
#include "ast.h"

struct env {
    struct array_kv vars;
    struct array_kv fns;
};

void env_new(struct env *env);
void env_free(struct env *env);

struct ast *env_get_var(struct env *env, const char *name);

struct ast *env_eval(struct env *env, const char *text);
