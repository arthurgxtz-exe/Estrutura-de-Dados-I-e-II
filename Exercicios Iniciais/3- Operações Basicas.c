#include <stdio.h>

int main(){

    float preco_litro, valor, litros;

    printf("Digite o preço do litro:");
    scanf("%f", &preco_litro);
    printf("Digite o valor que deseja abastecer:");
    scanf("%f", &valor);

    litros = valor / preco_litro;

    printf("Você irá abastecer %.3f litro(s)!", litros);
    
    return 0;
}