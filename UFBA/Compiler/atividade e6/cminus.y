%{
/* includes, C defs */

#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s, ...);
%}


/* declare tokens */
%token NUM
%token ID
%token ELSE 
%token IF 
%token INT 
%token RETURN 
%token VOID 
%token WHILE
%token EQ
%token NEQ
%token LT
%token GT
%token LTEQ
%token GTEQ
%token ERROR

%nonassoc EQ
%nonassoc NEQ
%nonassoc LT
%nonassoc GT
%nonassoc LTEQ
%nonassoc GTEQ

%start program

%%

program: declaration-list
;

declaration-list: 
  declaration-list declaration
| declaration
;

declaration:
  var-declaration 
| fun-declaration  
;

var-declaration: 
  type-specifier ID ';'
| type-specifier ID '[' NUM ']' ';'
;

fun-declaration: 
  type-specifier ID '(' params ')' compound-stmt
;

type-specifier: 
  INT  
| VOID 
;

params:
  param-list
| VOID 
;

param-list:
  param-list ',' param 
| param
;

param: 
  type-specifier ID
| type-specifier ID '[' ']'
;

compound-stmt: 
  '{' local-declarations statement-list '}' 
;

local-declarations: 
  local-declarations var-declaration
| /* empty */
;

statement-list:
  statement-list statement
| /* empty */
;

statement: 
  expression-stmt 
| compound-stmt 
| selection-stmt
| iteration-stmt 
| return-stmt 
;

expression-stmt: 
  expression ';'
| ';'           
;

selection-stmt: 
  IF '(' expression ')' statement
| IF '(' expression ')' statement ELSE statement 
;

iteration-stmt: 
  WHILE '(' expression ')' statement 
;

return-stmt: RETURN ';' 
| RETURN expression ';' 
;

expression: 
  var '=' expression
| simple-expression
;

var:  
  ID
| ID '[' expression ']'
;

simple-expression:
  additive-expression relop additive-expression 
| additive-expression
;

relop: LTEQ | LT | GT | GTEQ | EQ | NEQ
;

additive-expression: 
  term
| additive-expression '+' term
| additive-expression '-' term
;

term: 
  factor
| term '*' factor
| term '/' factor
;

factor: 
  NUM
| '(' expression ')'
| var 
| call 
;

call: 
  ID '(' args ')'
;

args:
  args-list
| /* empty */ 
;

args-list:
  args-list ',' expression  
| expression 
;

%%




