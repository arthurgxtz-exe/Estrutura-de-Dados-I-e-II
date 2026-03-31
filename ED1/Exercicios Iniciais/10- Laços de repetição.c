#include <stdio.h>
#include <stdlib.h>

int main(){

    int maior, menor, num;
    int cont, soma;
    float media;

    printf("Digite o 1° numero:\n");
    scanf("%d", &num);
    maior = num;
    menor = num;
    soma = 0;

    for (cont = 2; cont <= 10; cont++)
    {
        printf("Digite o %d° numero:\n", cont);
        scanf("%d", &num);
        soma = soma + num;
        
        if(num > maior )
        {
            maior = num; 
        }

        if(num < menor)
        {
            menor = num;
        }

    }

    media = (float)soma / 10;
    
    printf("Maior numero: %d\nMenor numero: %d\n", maior, menor);
    printf("Media simples dos valores lidos: %.2f\n", media);
   
    return 0;

}
