%option noyywrap

%{
#include <stdio.h>
#include "tokens.h"
%}

%{
#define YYERRCODE -1
%}


%%
not                     { return KW_NOT; }
NOT                     { return KW_NOT; }
and                     { return KW_AND; }
AND                     { return KW_AND; }
or                      { return KW_OR; }
OR                      { return KW_OR; }
equal                   { return KW_EQUAL; }
EQUAL                   { return KW_EQUAL; }
less                    { return KW_LESS; }
LESS                    { return KW_LESS; }
nil                     { return KW_NIL; }
NIL                     { return KW_NIL; }
list                    { return KW_LIST; }
LIST                    { return KW_LIST; }
append                  { return KW_APPEND; }
APPEND                  { return KW_APPEND; }
concat                  { return KW_CONCAT; }
CONCAT                  { return KW_CONCAT; }
set                     { return KW_SET; }
SET                     { return KW_SET; }
def                     { return KW_DEF; }
DEF                     { return KW_DEF; }
for                     { return KW_FOR; }
FOR                     { return KW_FOR; }
if                      { return KW_IF; }
IF                      { return KW_IF; }
exit                    { return KW_EXIT; }
EXIT                    { return KW_EXIT; }
load                    { return KW_LOAD; }
LOAD                    { return KW_LOAD; }
display                 { return KW_DISPLAY; }
DISPLAY                 { return KW_DISPLAY; }
true                    { return KW_TRUE; }
TRUE                    { return KW_TRUE; }
false                   { return KW_FALSE; }
FALSE                   { return KW_FALSE; }
\(                      { return OP_OP; }
\)                      { return OP_CP; }
\/                      { return OP_DIV; }
\*                      { return OP_MULT; }
\+                      { return OP_PLUS; }
\-                      { return OP_MINUS; }
,                       { return OP_COMMA; }
;;.*                    { return COMMENT; }
[0-9]+b[0-9]+           { return VALUEF; }
[a-zA-Z][a-zA-Z0-9]*    { return IDENTIFIER; }
[0-9]+                  { return VALUE_INT; }

\n                      { /* Newline, do nothing */ }
[ \t]                   { /* Whitespace, do nothing */ }
.                       { return YYERRCODE; }

%%

int yylex();


int main() {
    int token;
    while ((token = yylex()) != 0) {
        if (token == -1) {
            printf("SYNTAX_ERRORS cannot be tokenized\n");
        } else {
            switch(token){
                case 1:
                    printf("KW_NOT\n");
                    break;
                case 2:
                    printf("KW_AND\n");
                    break;
                case 3:
                    printf("KW_OR\n");
                    break;
                case 4:
                    printf("KW_EQUAL\n");
                    break;
                case 5:
                    printf("KW_LESS\n");
                    break;
                case 6:
                    printf("KW_NIL\n");
                    break;
                case 7:
                    printf("KW_LIST\n");
                    break;
                case 8:
                    printf("KW_APPEND\n");
                    break;
                case 9:
                    printf("KW_CONCAT\n");
                    break;
                case 10:
                    printf("KW_SET\n");
                    break;
                case 11:
                    printf("KW_DEF\n");
                    break;
                case 12:
                    printf("KW_FOR\n");
                    break;
                case 13:
                    printf("KW_IF\n");
                    break;
                case 14:
                    printf("KW_EXIT\n");
                    break;
                case 15:
                    printf("KW_LOAD\n");
                    break;
                case 16:
                    printf("KW_DISPLAY\n");
                    break;
                case 17:
                    printf("KW_TRUE\n");
                    break;
                case 18:
                    printf("KW_FALSE\n");
                    break;
                case 19:
                    printf("OP_OP\n");
                    break;
                case 20:
                    printf("OP_CP\n");
                    break;
                case 21:
                    printf("OP_DIV\n");
                    break;
                case 22:
                    printf("OP_MULT\n");
                    break;
                case 23:
                    printf("OP_PLUS\n");
                    break;
                case 24:
                    printf("OP_MINUS\n");
                    break;
                case 25:
                    printf("OP_COMMA\n");
                    break;
                case 26:
                    printf("VALUEF\n");
                    break;
                case 27:
                    printf("IDENTIFIER\n");
                    break;
                case 28:
                    printf("COMMENT\n");
                    break; 
                case 29:
                    printf("VALUE_INT\n");
                    break; 
            }
        }
    }
    return 0;
}
