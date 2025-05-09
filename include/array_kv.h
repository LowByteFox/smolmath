#pragma once

#include "ast.h"

#include <stddef.h>

/* how often to sort keys */
#define SORT_EVERY  4
#define KV_GROW     8

struct kv {
    const char *name;
    size_t len;
    struct ast *value;
};

struct array_kv {
    struct kv *arr;
    size_t allocated;
    size_t size;
};

void kv_free(struct array_kv *kv);

void kv_add(struct array_kv *kv, const char *name, struct ast *value);
struct ast *kv_get(struct array_kv *kv, const char *name);
