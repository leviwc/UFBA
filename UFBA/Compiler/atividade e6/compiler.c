#include "cminus.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int yyparse();
void yyerror(char *s, ...);


int main(int argc, char **argv) {
// using stdin and stdout
    int status = yyparse();

    if (!status) 
        printf("no syntax errors found\n");
}

void yyerror(char *s, ...) {
    extern int yylineno;
    va_list ap; va_start(ap, s);

    fprintf(stderr, "error at or before line %d: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    exit(0);
}


