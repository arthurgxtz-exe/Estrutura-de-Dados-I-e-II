#include <stdio.h>
#include <stdlib.h>


int main(){
    
    int cont, num, soma = 0, maior = 0, menor = 0, cont_validos = 0;
    int primeiro = 1;
    float media;

    printf("Digite o N° de números inteiros que vai digitar:\n");
    scanf("%d", &cont);
     
    for (int i = 1; i <= cont; i++)
    {
        printf("Digite o %d° número:\n", i);
        scanf("%d", &num);

        if(num > 0)
        {
            cont_validos++;
            soma = soma + num;

            if(primeiro == 1)
            {
                maior = num;
                menor = num;
                primeiro = 0;
            }
            if(num > maior)
            {
                maior = num;
            }
            if(num < menor)
            {
                menor = num;
            }
        }
                   
    }

    printf("\nA soma dos valores validos e: %d\n", soma);
    printf("O maior número valido: %d\nO menor numero valido: %d\n", maior, menor);
    if(cont_validos > 0)
    {
        media = (float)soma / cont_validos;
        printf("A média dos valores validos e de: %.2f\n", media);
    }
    else
    {
        printf("Não houve entradas de números válidos, para calcular uma média.\n");
    }
    
    return 0;
}