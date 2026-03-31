
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
srand(time(NULL));
    
    int numeros[25];
    int j, temp;
    
    for (int i = 0; i < 25; i++)
    {
        numeros[i] = i + 1;
    }
    for (int i = 24; i > 0; i--)
    {   
        j = rand() % i + 1;
        temp = numeros[i];
        numeros[i] = numeros[j];
        numeros [j] = temp;
    }

    printf("Números LotoFácil:\n");
    for(int i = 0; i < 15; i++)
    {
        printf("%d ", numeros[i]);
    }   
    printf("\n");
    printf("Númmeros não sorteados:\n");
    for(int i = 15; i < 25; i++)
    {
        printf("%d ", numeros[i]);
    }

    return 0;
}