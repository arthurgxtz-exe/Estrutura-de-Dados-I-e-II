#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int n;
    printf("Quantos números seerão sorteados?\n");
    scanf("%d", &n);
    int sorteio[n];
    int contagem[n + 1];
    for(int i = 0; i < n + 1; i++)
    {   
        contagem[i] = 0;
    }
    
    printf("Todos os números sorteados:\n");
    for(int i = 0; i < n; i++)
    {
        sorteio[i] = rand() % (n + 1);
        printf("%d ", sorteio[i]);
        contagem[sorteio[i]]++;
    }

    printf("\nOs valores que coincidiram com o próprio índice do vetor:\n");
    int coincidencia = 0;
    for(int i = 0; i < n; i++)
    {
        if(i == sorteio[i])
        {   
            printf("%d ", sorteio[i]);
            coincidencia = 1;
        }
    }
    if(!coincidencia)
        {
            printf("Nenhum número coincidiu.\n");
        } 

    printf("\nOs valores que não foram sorteados:\n");   
    for(int i = 0; i <= n; i++)
    {
        if(contagem[i] == 0)
        {
            printf("%d ", i);
        }
    }
        
    printf("\nOs valores sorteados repetidamente (mais de uma vez):\n");
    for(int i = 0; i <= n; i++)
    {
        
        if(contagem[i] > 1)
        {
            printf("%d ", i);
        }
    }
            

    int menor = sorteio[0]; 
    int maior = sorteio[n/2];
    
    
    for(int i = 1; i < (n /2)- 1; i++)
    {
        if(sorteio[i] < menor)    
        {
            menor = sorteio[i];
        }
    }
        
    printf("\nO menor valor da metade inicial é: %d\n", menor);
    
    for(int i = n / 2; i < n; i++)
    {
        
        if(sorteio[i] > maior)
        {
            maior = sorteio[i];
        }
    }
    printf("O maior valor da matade final é: %d\n", maior)  ;
    
    return 0;
}