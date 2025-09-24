#include <stdio.h>
#include <stdlib.h>

int main() {

    int n1, n2, div, resto;
    float typecast;

    printf("Digite o primeiro numero inteiro:\n");
    scanf("%d", &n1);
    printf("Digite o segundo numero inteiro:\n");
    scanf("%d", &n2);

    resto = n1 % n2;
    div = n1 / n2;
    typecast = (float)n1 / n2;

    printf("Divisão de dois numeros inteiros: %d / %d = %d\nResto da divisão inteira: %d\n", n1, n2, div, resto);
    printf("Divisão de dois numeros inteiros usando TypeCast: %d / %d = %f\n", n1, n2, typecast);

    return 0;

}