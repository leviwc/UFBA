#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int is_spacing(char c) { return ((c == ' ' || c == '\n' || c == '\t')); }
char* key[6] = {"else", "if", "int", "return", "void", "while"};
int main(int argc, char* argv[]) {
    FILE *source, *target;
    source = fopen(argv[1], "r");
    if (source == NULL) {
        printf("ERROR OPENNING FILE");
        return 0;
    }
    target = fopen(argv[2], "w");
    if (target == NULL) {
        printf("ERROR OPENNING FILE");
        return 0;
    }
    int c;
    int line_num = 1;
    c = fgetc(source);
    while (!feof(source)) {
        if (is_spacing(c)) {
            if (c == '\n') line_num++;
        } else if (isalpha(c)) {
            char id[100];
            int at = 0;
            while (isalnum(c)) {
                id[at] = c;
                at++;
                c = fgetc(source);
            }
            id[at] = '\0';
            ungetc(c, source);
            int iskey = 0;
            for (int i = 0; i < 6; i++) {
                if (strcmp(id, key[i]) == 0) {
                    iskey = 1;
                }
            }
            if (iskey) {
                fprintf(target, "(%d,KEY,\"%s\")\n", line_num, id);
            } else {
                fprintf(target, "(%d,ID,\"%s\")\n", line_num, id);
            }
        } else if (isdigit(c)) {
            fprintf(target, "(%d,NUM,\"", line_num);
            while (isdigit(c)) {
                fprintf(target, "%c", c);
                c = fgetc(source);
            }
            ungetc(c, source);
            fprintf(target, "\")\n");
        } else {
            if (c == '/') {
                c = getc(source);
                if (c == '/') {
                    while (c != '\n') {
                        c = getc(source);
                    }
                    line_num++;
                } else {
                    ungetc(c, source);
                    fprintf(target, "(%d,SYM,\"/\")\n", line_num);
                }
            } else if (c == '=' || c == '<' || c == '>') {
                char d = getc(source);
                if (d == '=') {
                    fprintf(target, "(%d,SYM,\"%c=\")\n", line_num, c);
                } else {
                    ungetc(d, source);
                    fprintf(target, "(%d,SYM,\"%c\")\n", line_num, c);
                }
            } else if (c == '+' || c == '-' || c == '*' || c == ';' ||
                       c == ',' || c == '(' || c == ')' || c == '[' ||
                       c == ']' || c == '{' || c == '}') {
                fprintf(target, "(%d,SYM,\"%c\")\n", line_num, c);
            } else if (c == '!') {
                c = getc(source);
                if (c == '=') {
                    fprintf(target, "(%d,SYM,\"!=\")\n", line_num);
                } else {
                    ungetc(c, source);
                    fprintf(target, "(%d,ERROR,\"!\")\n", line_num);
                }
            } else {
                fprintf(target, "(%d,ERROR,\"%c\")\n", line_num, c);
                fclose(source);
                fclose(target);
                return 0;
            }
        }
        c = fgetc(source);
    }
    fclose(source);
    fclose(target);
}