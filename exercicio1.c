#include <stdio.h>

int main() {
    // stop after preprocess use: gcc exercicio1.c -E
    // stop after assembling process use: gcc exercicio1.c -c
    // stop after proper compilation use: gcc exercicio1.c -S

    // change name file
    // receiving source code: gcc exercicio1.c
    // dont process source code: gcc exercicio1.i
    // Objjective-C source code: gcc exercicio1.m

    int a = 30 + 10;
    int b = 10 * a;
    return 0;
}