%{
#include "ast.h"
#include "parser.h"
#include <config.h>
%}

%%
"def"           return DEF_TOK;
[a-zA-Z]+       { yylval.str.str = yytext; yylval.str.len = yyleng; return VARIABLE_TOK; }
[0-9]+          { yylval.num = atol(yytext); return NUMBER_TOK; }
[0-9]+\.[0-9]+  { 
                #if BACKEND_FLOAT32
                yylval.flt = strtof(yytext, NULL);
                #elif BACKEND_FLOAT64
                yylval.flt = strtod(yytext, NULL);
                #elif BACKEND_FLOAT128
                yylval.flt = strtold(yytext, NULL);
                #endif
                return FLOAT_TOK;
                }
[ \t\n]         ;
[=(),]          return yytext[0];
"^"             return EXP_TOK;
"+"             return PLUS_TOK;
"-"             return MINUS_TOK;
"*"             return MUL_TOK;
"/"             return DIV_TOK;

.               { fprintf(stderr, "Unexpected character: %s!\n", yytext); abort(); }
%%

int yywrap(void) {
    return 1;
}
