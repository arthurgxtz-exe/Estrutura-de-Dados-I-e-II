#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int x, y, num, repetido;
    printf("Digite o tamanho do vetor x:\n");
    scanf("%d", &x);
    printf("Digite o tamanho do vetor y:\n");
    scanf("%d", &y);

    int vetx[x];
    int vety[y];
    int contagem[x + y + 1];

    for(int i = 0; i < (x + y + 1); i++)
    {
        contagem[i] = 0;
    }

    printf("\nVetores x:\n");
    for(int i = 0; i < x; i++)
    {
        do{
            num = rand() % (x + y + 1);
            repetido = 0;
            for(int j = 0; j < i; j++)
            {
                if(vetx[j] == num)
                {
                    repetido = 1;
                    break;
                }
            }
        }while(repetido);
        vetx[i] = num;
        printf("%d ", vetx[i]);
    }
    
    printf("\nVetores y:\n");
    for(int i = 0; i < y; i++)
    {
        do{
            num = rand() % (x + y + 1);
            repetido = 0;
            for(int j = 0; j < i; j++)
            {
                if(vety[j] == num)
                {
                    repetido = 1;
                    break;
                }
            }
        }while(repetido);
        vety[i] = num;
        printf("%d ", vety[i]);
    }
    for(int i = 0; i < x; i++)
    {
        contagem[vetx[i]] = 1;

    }
    for(int i= 0; i < y; i++)
    {
        if(contagem[vety[i]] == 1)
        {
            contagem[vety[i]] = 3;
        }
        else
        {
            contagem[vety[i]] = 2;
        }
    }
    printf("\nTodos os números exclusivos do vetor X:\n");
    for(int i = 0; i < (x + y + 1); i ++)
    {
        if(contagem[i] == 1)
        {
            printf("%d ", i);
        }
    }
    printf("\nTodos os números exclusivos do vetor y:\n");
    for(int i = 0; i < (x + y + 1); i++)
    {
        if(contagem[i] == 2)
        {
            printf("%d ", i);
        }
    }
    printf("\nOs números existentes nos dois vetores:\n");
    for(int i = 0; i < (x + y + 1); i++)
    {
        if(contagem[i] == 3)
        {
            printf("%d ", i);
        }

    }

    return 0;
}