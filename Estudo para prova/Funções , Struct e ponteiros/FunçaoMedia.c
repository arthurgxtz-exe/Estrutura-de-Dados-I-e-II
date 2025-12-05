#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

float calcularMedia(float n1, float n2){

    return (n1 + n2) / 2 ;
}

float calcularPrecoFinal(float n1, int n2){

    return n1 * n2;
}

int main() {

    float nota1, nota2;
    printf("Digite as duas notas do aluno separado por espaço:\n");
    scanf("%f %f", &nota1, &nota2);
    printf("A média das duas notas é: %.2f\n", calcularMedia(nota1, nota2));
    Sleep(600);
    system("cls");

    float preco;
    int qtd;

    printf("Qual o preço do produto?\n");
    scanf("%f", &preco);
    printf("Qual a quantidade comprada?\n");
    scanf("%d", &qtd);
    printf("O preço final é: %2.f", calcularPrecoFinal(preco, qtd));

    return 0;
}