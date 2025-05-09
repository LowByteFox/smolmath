#include "array_kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmp(const void *a, const void *b);
static struct kv *find(struct array_kv *kv, const char *name);

void kv_free(struct array_kv *kv)
{
    free(kv->arr);
    kv->allocated = 0;
    kv->size = 0;
}

void kv_add(struct array_kv *kv, const char *name, struct ast *value)
{
    if (kv->allocated == kv->size)
        kv->arr = realloc(kv->arr, (kv->allocated += KV_GROW) * sizeof(struct kv));

    struct kv *ptr = find(kv, name);
    if (ptr) {
        ptr->value = value;
        return;
    }

    kv->arr[kv->size].name = name;
    kv->arr[kv->size].len = strlen(name);
    kv->arr[kv->size].value = value;

    kv->size++;

    if (kv->size % SORT_EVERY == 0)
        qsort(kv->arr, kv->size, sizeof(struct kv), cmp);
}

static struct kv *find(struct array_kv *kv, const char *name)
{
    size_t len = strlen(name);

    for (size_t i = 0; i < kv->size; i++) {
        struct kv *ptr = kv->arr + i;

        if (ptr->len == len && ptr->name[0] == name[0] && strcmp(ptr->name, name) == 0)
            return ptr;
    }

    return NULL;
}

struct ast *kv_get(struct array_kv *kv, const char *name)
{
    size_t len = strlen(name);

    for (size_t i = 0; i < kv->size; i++) {
        struct kv *ptr = kv->arr + i;

        if (ptr->len == len && ptr->name[0] == name[0] && strcmp(ptr->name, name) == 0)
            return ptr->value;
    }

    return NULL;
}

static int cmp(const void *a, const void *b)
{
    const struct kv *ak = a;
    const struct kv *bk = b;

    return strcmp(ak->name, bk->name);
}
