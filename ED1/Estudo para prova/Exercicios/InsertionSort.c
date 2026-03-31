#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int n = 5;
    int vet[5] = {5, 3, 4, 1, 2};

    printf("Vetor Original:\n");
    for(int i = 0; i < n; i++)
    {
       
        printf("%d ", vet[i]);
    }

    
    for( int i = 1; i < n; i++)
    {
        int chave = vet[i];
        int j = i - 1;

        while(j >= 0 && vet[j] > chave)
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = chave;
    }


    printf("\nVetor ordenado:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }

    return 0;
}