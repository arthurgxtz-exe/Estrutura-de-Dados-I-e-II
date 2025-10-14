#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int vet[100];
    int j, x, cont = 0;

    
    for (int i = 0; i < 100; i++)
    {
        vet[i] = rand() % 20 + 1;
    }

    do{
        cont = 0;
        printf("Digite um valor X para buscar no vetor ou (<= 0 para sair):\n");
        scanf("%d", &x);
        if(x > 0){

            for (j = 0; j < 100; j++)
            {
                if(vet[j] == x )
                {
                    cont++;
                    printf("O vetor[%d] tem o valor de: *%d*\n", j, vet[j]);
                }
                else
                {
                    printf("O vetor[%d] tem o valor de: %d\n", j, vet[j]);
                }
            }
            printf("Houve %d ocorrências do número %d\n",  cont, x);
        }
               
   
    }while(x > 0);
                          
    printf("Programa Finalizado\n");
    return 0;
}