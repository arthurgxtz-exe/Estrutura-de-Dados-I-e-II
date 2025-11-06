
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int vet[30];
    int total = 0;
    float media;
    int maior, menor, dia_maior, dia_menor, cont = 0;
    
    int primeiro = 1;
    for(int i = 0; i < 30; i++)
    {
        vet[i] = rand() % (80 - 12 + 1) + 12;
        total+=vet[i];
        if(primeiro)
        {
            maior = vet[i];
            menor = vet[i];
            dia_maior = i + 1;
            dia_menor = i + 1;
            primeiro = 0;
        } 
        if(vet[i] > maior)       
        {
            maior = vet[i];
            dia_maior = i + 1;
        }
        if(vet[i] < menor)
        {
            menor = vet[i];
            dia_menor = i + 1;
        }
    }
    media = (float)total / 30;
    for(int i = 0; i < 30; i++)
    {
        if(vet[i] > media)
        {
            cont++;
        }
    }

    printf("O dia com maior humidade relativa foi o dia %d, que teve: %d\n", dia_maior, maior);
    printf("O dia com menor humidade relativa foi o dia %d, que teve: %d\n", dia_menor, menor);
    printf(" A média de de humidade relativa do mês foi de: %.2f\n", media);
    printf("Foram %d dias no mês de humidadee relativa acima da média\n", cont);


    return 0;
}