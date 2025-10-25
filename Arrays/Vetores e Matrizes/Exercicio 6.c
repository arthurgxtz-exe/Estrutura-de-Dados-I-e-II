#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
srand(time(NULL));

    int n;
    
    printf("Digite um valor, para ser o  tamanho da tabela:\n");
    scanf("%d", &n);
    while(getchar()!= '\n');
    
    
    int matriz[n][n];
    int soma_coluna = 0;
    int soma_linha = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i == j)
            {
                matriz[i][j] = 0;
            }
            else
            {
                matriz[i][j] = rand() % 10 + 1;
            }

        }
    }
    for(int i = 0; i < n ; i++)
    {
        soma_linha = 0;
        soma_coluna = 0;

        for(int j = 0; j < n; j++)
        {
           soma_linha+= matriz[i][j];
           soma_coluna+= matriz[j][i];
            
        }
        matriz[i][i] = soma_coluna + soma_linha;

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