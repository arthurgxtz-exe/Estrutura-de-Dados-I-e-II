#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int n, x;

    printf("Digite um valor, para ser o  tamanho da tabela:\n");
    scanf("%d", &n);
    fflush(stdin);
    printf("A tabela será prenchida com n° aleatórios entre 1 e ...?\n");
    scanf("%d", &x);
    fflush(stdin);
    system("cls");

    int matriz[n][n];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matriz[i][j] = rand() % x + 1;
        }
    }
            
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {   
            printf("%d\t", matriz[i][j]);
        }

       printf("\n");
    }
return 0;
}