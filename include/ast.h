#pragma once

#include <config.h>

enum node_type {
    NUMBER,
    VARIABLE,
    BRACKETS,
    ADD,
    SUB,
    MUL,
    DIV,
    EXP,
    ASSIGN,
    C_FN,
    FUNCTION_DEF,
    FUNCTION_CALL,
    FUNCTION_ARG,
};

struct str {
    char *str;
    int len;
};

struct ast {
    enum node_type type;
    union {
#if BACKEND_FLOAT32
        float value;
#elif BACKEND_FLOAT64
        double value;
#elif BACKEND_FLOAT128
        long double value;
#endif
        char *name;
        struct ast *bracket;
        struct {
            struct ast *left;
            struct ast *right;
        } operation;
        struct {
            char *name;
            struct ast *value;
        } assign;
        struct {
            char *name;
            struct ast *expr;
        } fn_def;
        struct {
            char *name;
            struct ast *first_arg;
        } fn_call;
        struct {
            struct ast *expr;
            struct ast *next_arg;
        } fn_arg;
        struct {
            const char *name;
            struct ast *(*fun)(struct ast *first_arg);
        } c_fn;
    };
};

#if BACKEND_FLOAT32
struct ast *number_node(float value);
#elif BACKEND_FLOAT64
struct ast *number_node(double value);
#elif BACKEND_FLOAT128
struct ast *number_node(long double value);
#endif
struct ast *variable_node(struct str str);
struct ast *bracket_node(struct ast *expr);
struct ast *operation_node(enum node_type type, struct ast *left, struct ast *right);
struct ast *assign_node(struct str str, struct ast *expr);
struct ast *fn_def_node(struct str str, struct ast *expr);
struct ast *fn_call_node(struct str str, struct ast *arg);
struct ast *fn_arg_node(struct ast *list, struct ast *expr);

void describe_node(struct ast *ast);
void free_node(struct ast *ast);

struct ast *parse(const char *str);
