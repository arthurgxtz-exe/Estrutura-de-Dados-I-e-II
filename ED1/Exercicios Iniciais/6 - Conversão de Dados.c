#include <stdio.h>
#include <stdlib.h>

int main(){

    char n1;
    int n2, mult, newN1;

    printf("Digite um número de 0 a 9:\n");
    scanf("%c", &n1);
    printf("Digite um número inteiro:\n");
    scanf("%d", &n2);
    
    mult = n1 * n2;
    printf("%c * %d = %d\n", n1, n2, mult); // Sem conversão percebi que a multiplicação ocorre pelo código ASCII do caractere, e não o número.
    newN1 = n1 - '0'; // "Pegue o valor numérico (código ASCII) que está na variável n1 e subtraia dele o valor numérico (código ASCII) do caractere '0'."
    mult = newN1 * n2;
    printf("%d * %d = %d\n", newN1, n2, mult); // Agora sim, com o char convertido para int, o resultado da multiplicação é correta.
    //Em resumo: subtrair '0' é a técnica padrão em C para remover o "deslocamento" da Tabela ASCII e encontrar o valor numérico real de um caractere de dígito.
    return 0;

}