#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char modelo[50];
    int ano;
    float preco;
}Carro;

void imprimirCarro(Carro c) {
    printf("\n--- Ficha do Carro ---\n");
    printf("Modelo: %s\n", c.modelo);
    printf("Ano: %d\n", c.ano);
    printf("Preco: R$ %.3f\n", c.preco);
}

int main() {
    int n;
    printf("Digite o numero de carros que você deseja cadastrar:\n");
    scanf("%d", &n);
    
    Carro garagem[n];

    printf("==== CADASTRO DE %d CARROS ===\n", n);

    for(int i = 0; i < n; i++){
        while(getchar()!='\n');

        printf("\nDigite os dados do carro número %d:\n", i + 1);
        printf("Modelo:\n");
        scanf(" %[^\n]", garagem[i].modelo);
        printf("Ano:\n");
        scanf("%d", &garagem[i].ano);
        printf("Preco:\n");
        scanf("%f", &garagem[i].preco);
    }

    printf("\nRelátorio:\n");

    for(int i = 0; i < n; i++){
        imprimirCarro(garagem[i]);

       
    }

    return 0;
};