#include <stdio.h> 

int main(){

    int num1, num2;
    int soma, sub, mult, qs;
    float div;

    printf("Digite o primeiro número:");
    scanf("%d", &num1);
    printf("Digite o segundo número:");
    scanf("%d", &num2);

    soma = num1 + num2;
    sub = num1 - num2;
    mult = num1 * num2;
    div = (float)num1 / num2;
    qs = (num1 - num2) * (num1 - num2);

    printf("\n--- Resultados ---\n");
    printf("Soma: %d\n", soma);
    printf("Subtracao: %d\n", sub);
    printf("Multiplicacao: %d\n", mult);
    printf("Divisao: %.2f\n", div);
    printf("Quadrado da subtracao: %d\n", qs);

    return 0;
}
