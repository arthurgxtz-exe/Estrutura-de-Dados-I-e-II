#include <stdio.h>
#include <stdlib.h>

typedef struct Caixa{
    int num;
    struct Caixa *proxima;
} Caixa;

int main() {

    Caixa *caixa1 = (Caixa*) malloc(sizeof(Caixa));
    Caixa *caixa2 = (Caixa*) malloc(sizeof(Caixa));

    caixa1->num = 10;
    caixa2->num = 20;

    caixa2->proxima = NULL;
    caixa1->proxima = caixa2;

    printf("VAlor da caixa 1: %d\n", caixa1->num);

    printf("Valor da Caixa 2: %d\n", caixa1->proxima->num);

    free(caixa1);
    free(caixa2);

    return 0;
}