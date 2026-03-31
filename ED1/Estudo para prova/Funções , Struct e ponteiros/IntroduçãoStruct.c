#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct carro{
    char modelo[50];
    int ano;
    float preco;
};

void imprimirCarro(struct carro c){
   printf("--- Ficha do Carro ---\n");
   printf("O modelo do carro é: %s\n", c.modelo);
   printf("O ano do carro é: %d\n", c.ano);
   printf("O preço do carro é: %.3f\n", c.preco);
}
int main() {
    struct carro speed;
    printf("Digite o modelo do carro:\n");
    scanf(" %[^\n]s", speed.modelo);

    printf("Digite o ano do carro:\n");
    scanf("%d", &speed.ano);

    printf("Digite o preço do carro:\n");
    scanf("%f", &speed.preco);

    system("cls");
    
   imprimirCarro(speed);


    return 0;
}