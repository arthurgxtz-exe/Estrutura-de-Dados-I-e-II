#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int n, aux, h_index = 0;
    printf("Digite quantos artigos você tem:");
    scanf("%d", &n);
    int citacoes[n];
    printf("Citações:\n");
    for(int i = 0; i < n; i++)
    {
        citacoes[i] = rand() % n + 1;
        printf("%d ", citacoes[i]);
    }
    for(int i = 0; i < n - 1; i++) 
    {
        for(int j = i + 1; j < n; j++)
        {
            if(citacoes[j] > citacoes[i])
            {
                aux = citacoes[i];
                citacoes[i] = citacoes[j];
                citacoes[j] = aux;
            }
        }
    }
   printf("\n");
    for(int i = 0; i < n; i++)
    {   
        if(citacoes[i] >= i + 1)
        {
            h_index = i + 1;
        }
    }
        
    printf("\nH_index: %d\n", h_index);
return 0;
}