#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));  

    int n, x, y, aux;
    printf("Digite quantos números serão sorteados:\n");
    scanf("%d", &n);
    printf("Você deseja sortear um número em qual intervalo:(X Y)\n");
    scanf("%d %d", &x, &y);

    int numeros[n];
    int usados[n];
    
    for(int i = 0; i < n; i++)
    {
        usados[i]  = 0;
    }

    printf("Números sorteados:\n");
    for(int i = 0; i < n; i++)
    {
        numeros[i] = rand() % (y - x + 1) + x;
        
        printf("%d ", numeros[i]);
    }
    
    printf("\n");

    int trocas = 0;

    while(1){
        int maior = -1, menor  = -1;
        int i_maior = -1, i_menor = -1;

        for(int i = 0; i < n; i++)
        {
            if(usados[i] == 0)
            {
                if(maior == -1 || numeros[i] > maior)
                {
                    maior = numeros[i];
                    i_maior = i;
                }
                if(menor == -1 || numeros[i] < menor)
                {
                    menor = numeros[i];
                    i_menor = i;
                }
            }
        }
            
        if (i_maior == -1 || i_menor == -1 || i_maior == i_menor)
        break;

        aux = numeros[i_maior];
        numeros[i_maior] = numeros[i_menor];
        numeros[i_menor] = aux;

        usados[i_maior] = 1;
        usados[i_menor] = 1;
        trocas++;

        printf("%d° troca: ", trocas);
        for(int i = 0; i < n; i++) 
        {
            printf("%d ", numeros[i]);
        }
        
        printf("\n");
    }
    
    return 0;
}

