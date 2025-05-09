%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex(void);
int yyerror(const char *s);
extern int yy_flex_debug;

void yy_scan_string(const char *str);
static struct ast *root;
%}

%union {
    uint64_t num;
    struct str str;
    struct ast *ast;
}

%token <num> NUMBER_TOK
%token DEF_TOK
%token <str> VARIABLE_TOK
%type <ast> expr statement arg_list

%left PLUS_TOK MINUS_TOK
%left MUL_TOK DIV_TOK
%left EXP_TOK

%%
input:
     statement                          { root = $1; }
     ;

statement:
    DEF_TOK VARIABLE_TOK '=' expr       { $$ = fn_def_node($2, $4); }
    | VARIABLE_TOK '=' expr             { $$ = assign_node($1, $3); }
    | expr                              { $$ = $1; }
    ;

arg_list:
    expr                                { $$ = fn_arg_node(NULL, $1); }
    | expr ',' arg_list                 { $$ = fn_arg_node($3, $1); }
    |                                   { $$ = NULL; }
    ;

expr:
    NUMBER_TOK                          { $$ = number_node($1); }
    | VARIABLE_TOK                      { $$ = variable_node($1); }
    | expr PLUS_TOK expr                { $$ = operation_node(ADD, $1, $3); }
    | expr MINUS_TOK expr               { $$ = operation_node(SUB, $1, $3); }
    | expr MUL_TOK expr                 { $$ = operation_node(MUL, $1, $3); }
    | expr DIV_TOK expr                 { $$ = operation_node(DIV, $1, $3); }
    | expr EXP_TOK expr                 { $$ = operation_node(EXP, $1, $3); }
    | '(' expr ')'                      { $$ = bracket_node($2); }
    | VARIABLE_TOK '(' arg_list ')'     { $$ = fn_call_node($1, $3); }
    ;
%%

struct ast *parse(const char *str) {
    yy_scan_string(str);
    yyparse();
    return root;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
