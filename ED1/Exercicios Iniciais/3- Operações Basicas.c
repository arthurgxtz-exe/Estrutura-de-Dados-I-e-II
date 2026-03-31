#include <stdio.h>

int main(){

    float preco_litro, valor, litros;

    printf("Digite o preço do litro:\n");
    scanf("%f", &preco_litro);
    printf("Digite o valor que deseja abastecer:\n");
    scanf("%f", &valor);

    litros = valor / preco_litro;

    printf("Você irá abastecer %.3f litro(s)!\n", litros);
    
    return 0;
}